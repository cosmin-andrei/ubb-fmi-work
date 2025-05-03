import React, { useEffect, useReducer } from 'react';
import { getLogger } from '../core';
import { ItemProps } from './ItemProps';
import { getItems } from './itemApi';
import { StorageService } from './storageService';

const log = getLogger('ItemProvider');

export interface ItemsState {
    questions: ItemProps[],
    fetching: boolean,
    fetchingError?: Error | null,
    downloadProgress: string,
    fetchQuestions?: () => void;
}

interface ActionProps {
    type: string,
    payload?: any,
}

const initialState: ItemsState = {
    questions: StorageService.getData<ItemProps[]>("questions") || [],
    fetching: false,
    downloadProgress: '',
};

const FETCH_ITEMS_STARTED = 'FETCH_ITEMS_STARTED';
const FETCH_ITEMS_PROGRESS = 'FETCH_ITEMS_PROGRESS';
const FETCH_ITEMS_SUCCEEDED = 'FETCH_ITEMS_SUCCEEDED';
const FETCH_ITEMS_FAILED = 'FETCH_ITEMS_FAILED';

const reducer: (state: ItemsState, action: ActionProps) => ItemsState =
    (state, { type, payload }) => {
        switch (type) {
            case FETCH_ITEMS_STARTED:
                return { ...state, fetching: true, fetchingError: null, downloadProgress: 'Downloading 0/0' };
            case FETCH_ITEMS_PROGRESS:
                return { ...state, downloadProgress: `Downloading ${payload.m}/${payload.n}` };
            case FETCH_ITEMS_SUCCEEDED:
                return { ...state, questions: payload.questions, fetching: false, downloadProgress: 'Download complete' };
            case FETCH_ITEMS_FAILED:
                return { ...state, fetchingError: payload.error, fetching: false, downloadProgress: 'Download failed' };
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

    useEffect(() => {
        fetchAllQuestions();
    }, []);

    async function fetchAllQuestions() {
        try {
            log('Fetching all questions from server...');
            dispatch({ type: FETCH_ITEMS_STARTED });

            const storedIds = StorageService.getData<number[]>("questionIds") || [];
            let uniqueQuestions: ItemProps[] = [];
            let seenIds = new Set();

            for (let i = 0; i < storedIds.length; i++) {
                const question = await getItems([storedIds[i]]);
                if (!seenIds.has(question[0].id)) {
                    uniqueQuestions.push(question[0]);
                    seenIds.add(question[0].id);
                }

                // ✅ Afișează progresul în timp real
                dispatch({ type: FETCH_ITEMS_PROGRESS, payload: { m: i + 1, n: storedIds.length } });
                await new Promise(resolve => setTimeout(resolve, 300)); // Mic delay pentru a forța update-ul UI-ului
            }

            StorageService.saveData("questions", uniqueQuestions);
            dispatch({ type: FETCH_ITEMS_SUCCEEDED, payload: { questions: uniqueQuestions } });

        } catch (error) {
            log('Failed to fetch questions', error);
            dispatch({ type: FETCH_ITEMS_FAILED, payload: { error } });
        }
    }

    return (
        <ItemContext.Provider value={{ ...state, fetchQuestions: fetchAllQuestions }}>
            {children}
        </ItemContext.Provider>
    );
};
