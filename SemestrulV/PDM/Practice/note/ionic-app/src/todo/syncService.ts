import {StorageService} from "./storageService";
import {ItemProps} from "./ItemProps";
import {deleteItem} from "./itemApi";

export class SyncService {
    private static retryInterval = 20000;
    private static maxRetryInterval = 60000;
    private static SYNC_QUEUE_KEY = "syncQueue";

    static addToQueue(item: ItemProps): void {
        const queue = StorageService.getData<ItemProps[]>(this.SYNC_QUEUE_KEY) || [];
        if (!queue.some(q => q.id === item.id)) {
            queue.push(item);
            StorageService.saveData(this.SYNC_QUEUE_KEY, queue);
            console.warn(`Message ${item.id} added to sync queue`);
        }
    }

    static removeFromQueue(id: number): void {
        const queue = StorageService.getData<ItemProps[]>(this.SYNC_QUEUE_KEY) || [];
        const updatedQueue = queue.filter(item => item.id !== id);
        StorageService.saveData(this.SYNC_QUEUE_KEY, updatedQueue);
        console.log(`Message ${id} removed from sync queue`);
    }

    static async processQueue(): Promise<void> {
        const queue = StorageService.getData<ItemProps[]>(this.SYNC_QUEUE_KEY) || [];
        if (queue.length === 0) return;

        console.log(`Attempting to sync ${queue.length} messages...`);
        const remainingQueue: ItemProps[] = [];

        for (const item of queue) {
            try {
                if (item.deleted) {
                    await deleteItem(item.id!);
                    console.log(`Successfully synced deleted message ${item.id}`);
                    this.removeFromQueue(item.id!);
                }
            } catch (error) {
                console.warn(`Failed to sync message ${item.id}, will retry later`, error);
                remainingQueue.push(item);
            }
        }

        StorageService.saveData(this.SYNC_QUEUE_KEY, remainingQueue);
    }

    static startSyncInterval(): void {
        setInterval(() => {
            SyncService.processQueue();
        }, this.retryInterval);
    }
}
