import axios from 'axios';
import { baseUrl, getLogger, withLogs } from '../core';
import { ItemProps } from './ItemProps';

const itemUrl = `http://${baseUrl}/message`;

export const getItems: () => Promise<ItemProps[]> = () => {
    return withLogs(axios.get(itemUrl), 'getItems');
}

export const createItem: (item: ItemProps) => Promise<ItemProps[]> = (item) => {
    return withLogs(axios.post(itemUrl, item), 'createItem');
}

export const updateItem: (item: ItemProps) => Promise<ItemProps[]> = (item) => {
    console.log("Updating item:", item);
    return withLogs(axios.put(`${itemUrl}/${item.id}`, item), 'updateItem');
}


//AICI MODIFIC IN FUNCTIE DE CE IMI VINE DE LA SERVER!!!!
interface MessageData {
    id: number;
    text: string;
    read: boolean;
    sender: string;
    created: number;
}


const log = getLogger('ws');

export const newWebSocket = (onMessage: (data: MessageData) => void) => {
    const ws = new WebSocket(`ws://${baseUrl}`);
    ws.onopen = () => {
        log('web socket onopen');
    };
    ws.onclose = () => {
        log('web socket onclose');
    };
    ws.onerror = error => {
        log('web socket onerror', error);
    };
    ws.onmessage = messageEvent => {
        log('web socket onmessage');
        const newMessage = JSON.parse(messageEvent.data);
        onMessage(newMessage);
    };
    return () => {
        ws.close();
    }
}
