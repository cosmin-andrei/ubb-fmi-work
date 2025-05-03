import React, { useEffect, useReducer, useRef } from 'react';
import { getLogger } from '../core';
import { ItemProps } from './ItemProps';
import { getItems } from './itemApi';

const log = getLogger('ItemProvider');

export interface ItemsState {
    items: ItemProps[];
    fetching: boolean;
    fetchingError?: Error | null;
    saving: boolean;
    savingError?: Error | null;
}

interface ActionProps {
    type: string;
    payload?: any;
}

const initialState: ItemsState = {
    items: [],
    fetching: false,
    saving: false,
};

const FETCH_ITEMS_STARTED = 'FETCH_ITEMS_STARTED';
const FETCH_ITEMS_SUCCEEDED = 'FETCH_ITEMS_SUCCEEDED';
const FETCH_ITEMS_FAILED = 'FETCH_ITEMS_FAILED';
const UPDATE_ITEMS_FROM_WS = 'UPDATE_ITEMS_FROM_WS';

const reducer: (state: ItemsState, action: ActionProps) => ItemsState = (state, { type, payload }) => {
    switch (type) {
        case FETCH_ITEMS_STARTED:
            return { ...state, fetching: true, fetchingError: null };
        case FETCH_ITEMS_SUCCEEDED:
            return {
                ...state,
                items: Array.isArray(payload.items) ? payload.items : [],
                fetching: false
            };
        case FETCH_ITEMS_FAILED:
            return { ...state, fetchingError: payload.error, fetching: false };
        case UPDATE_ITEMS_FROM_WS: {
            const { event, note } = payload;
            let updatedItems = [...state.items];

            if (event === 'deleted') {
                updatedItems = updatedItems.filter(i => i.id !== note.id);
            } else if (event === 'inserted' || event === 'updated') {
                const existingIndex = updatedItems.findIndex(i => i.id === note.id);
                if (existingIndex !== -1) {
                    updatedItems[existingIndex] = note;
                } else {
                    updatedItems.push(note);
                }
            }

            return { ...state, items: updatedItems };
        }
        default:
            return state;
    }
};

export const ItemContext = React.createContext<ItemsState>(initialState);

interface ItemProviderProps {
    children: React.ReactNode;
}

export const ItemProvider: React.FC<ItemProviderProps> = ({ children }) => {
    const [state, dispatch] = useReducer(reducer, initialState);
    const { items, fetching, fetchingError, saving, savingError } = state;
    const isMounted = useRef(true);

    useEffect(() => {
        isMounted.current = true;
        fetchItems();
        return () => {
            isMounted.current = false;
        };
    }, []);

    async function fetchItems() {
        try {
            log('fetchItems started');
            dispatch({ type: FETCH_ITEMS_STARTED });

            let allItems: ItemProps[] = [];
            let page = 1;
            let newItems: ItemProps[];

            do {
                const response = await getItems(page);
                newItems = response.notes;
                allItems = [...allItems, ...newItems];
                page++;
            } while (newItems.length > 0);

            if (isMounted.current) {
                log('fetchItems succeeded');
                dispatch({ type: FETCH_ITEMS_SUCCEEDED, payload: { items: allItems } });
            }
        } catch (error) {
            if (isMounted.current) {
                log('fetchItems failed', error);
                dispatch({ type: FETCH_ITEMS_FAILED, payload: { error } });
            }
        }
    }

    interface WebSocketMessage {
        event: 'inserted' | 'updated' | 'deleted';
        note: ItemProps;
    }

    const newWebSocket = (onMessage: (message: WebSocketMessage) => void) => {
        const ws = new WebSocket(`ws://localhost:3000`);

        ws.onopen = () => {
            log("🔗 WebSocket connected");
        };

        ws.onmessage = (messageEvent) => {
            try {
                const message: WebSocketMessage = JSON.parse(messageEvent.data);
                onMessage(message);
            } catch (error) {
                console.error("Error parsing WebSocket message:", error);
            }
        };

        ws.onerror = (error) => {
            console.error("WebSocket encountered an error:", error);
        };

        ws.onclose = () => {
            log("WebSocket closed, attempting to reconnect...");
            setTimeout(() => newWebSocket(onMessage), 5000);
        };

        return () => {
            ws.close();
            log("WebSocket disconnected");
        };
    };

    useEffect(() => {
        let canceled = false;
        log('wsEffect - connecting');

        const closeWebSocket = newWebSocket((message: WebSocketMessage) => {
            if (canceled) {
                return;
            }
            const { event, note } = message;
            log(`ws message, event: ${event}`);

            dispatch({ type: UPDATE_ITEMS_FROM_WS, payload: { event, note } });
        });

        return () => {
            log('wsEffect - disconnecting');
            canceled = true;
            closeWebSocket?.();
        };
    }, []);

    return (
        <ItemContext.Provider value={{ items, fetching, fetchingError, saving, savingError }}>
            {children}
        </ItemContext.Provider>
    );
};
