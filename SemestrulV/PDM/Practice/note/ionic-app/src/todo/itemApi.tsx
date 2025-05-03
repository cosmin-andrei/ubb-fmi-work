import axios from 'axios';
import { baseUrl } from '../core';
import { ItemProps } from './ItemProps';
import { StorageService } from './storageService';
import { SyncService } from './syncService';

const itemUrl = `http://${baseUrl}/note`;
const LAST_MODIFIED_KEY = 'lastModified';

interface ServerResponse {
    notes: ItemProps[];
    page: number;
    more: boolean;
}

export const getItems = async (page: number = 1): Promise<ServerResponse> => {
    try {
        const lastModified = StorageService.getData<string>(LAST_MODIFIED_KEY);
        const headers: Record<string, string> = {};

        if (lastModified) {
            headers['If-Modified-Since'] = lastModified;
        }

        const response = await axios.get<ServerResponse>(`${itemUrl}?page=${page}`, {
            headers,
            validateStatus: (status) => status === 200 || status === 304
        });

        if (response.status === 304) {
            console.log(`Server returned 304, using cached data for page ${page}`);
            const cachedPageData = StorageService.getData<ServerResponse>(`notes-page-${page}`);

            if (cachedPageData) {
                console.log(`Found cached data for page ${page}`, cachedPageData);
                return cachedPageData;
            } else {
                console.warn(`No cached data found for 304 response, page: ${page}. Re-fetching page.`);

               const freshResponse = await axios.get<ServerResponse>(`${itemUrl}?page=${page}`);
                if (freshResponse.status === 200 && freshResponse.data.notes.length > 0) {
                    StorageService.saveData(`notes-page-${page}`, freshResponse.data);
                    return freshResponse.data;
                }

                return { notes: [], page, more: false };
            }
        }

        if (response.data) {
            const newLastModified = response.headers['last-modified'];
            if (newLastModified) {
                StorageService.saveData(LAST_MODIFIED_KEY, newLastModified);
            }

            console.log(`Saving new data to cache for page ${page}`, response.data);
            StorageService.saveData(`notes-page-${page}`, response.data);
            return response.data;
        }

        return { notes: [], page, more: false };
    } catch (error) {
        console.error(`Error fetching items for page ${page}:`, error);

        const cachedData = StorageService.getData<ServerResponse>(`notes-page-${page}`);
        if (cachedData) {
            console.log(`Using cached data due to error for page ${page}`, cachedData);
            return cachedData;
        }

        return { notes: [], page, more: false };
    }
};



export const deleteItem = async (id: number): Promise<void> => {
    try {
        await axios.delete(`${itemUrl}/${id}`);
    } catch (error) {
        console.error(`Error deleting item ${id}:`, error);
        throw error;
    }
};

