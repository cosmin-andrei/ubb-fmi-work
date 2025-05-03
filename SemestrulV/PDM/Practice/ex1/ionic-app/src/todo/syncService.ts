import { updateItem } from './itemApi';
import { StorageService } from './storageService';
import { ItemProps } from './ItemProps';

const SYNC_QUEUE_KEY = "syncQueue";

export class SyncService {
    static addToQueue(item: ItemProps): void {
        const queue = StorageService.getData<ItemProps[]>(SYNC_QUEUE_KEY) || [];
        queue.push(item);
        StorageService.saveData(SYNC_QUEUE_KEY, queue);
        console.warn(`Message ${item.id} added to sync queue`);
    }

    static async processQueue(): Promise<void> {
        const queue = StorageService.getData<ItemProps[]>(SYNC_QUEUE_KEY) || [];
        if (queue.length === 0) return;

        console.log(`Attempting to sync ${queue.length} messages...`);

        const remainingQueue: ItemProps[] = [];

        for (const item of queue) {
            try {
                await updateItem(item);
                console.log(`Successfully synced message ${item.id}`);
            } catch (error) {
                console.warn(`Failed to sync message ${item.id}, will retry later`, error);
                remainingQueue.push(item);
            }
        }

        StorageService.saveData(SYNC_QUEUE_KEY, remainingQueue);
        if (remainingQueue.length > 0) {
            console.warn(`${remainingQueue.length} messages left in sync queue.`);
        } else {
            console.log("All messages successfully synced!");
        }
    }

    static clearQueue(): void {
        StorageService.saveData(SYNC_QUEUE_KEY, []);
    }

    static startSyncInterval(): void {
        setInterval(() => {
            SyncService.processQueue();
        }, 10000);
    }
}
