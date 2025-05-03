export class StorageService {
    static saveData<T>(key: string, data: T): void {
        try {
            localStorage.setItem(key, JSON.stringify(data));
        } catch (error) {
            console.error(`Error saving ${key} to localStorage`, error);
        }
    }

    static getData<T>(key: string): T | null {
        try {
            const storedData = localStorage.getItem(key);
            return storedData ? JSON.parse(storedData) as T : null;
        } catch (error) {
            console.error(`Error getting ${key} from localStorage`, error);
            return null;
        }
    }

    static removeData(key: string): void {
        try {
            localStorage.removeItem(key);
        } catch (error) {
            console.error(`Error removing ${key} from localStorage`, error);
        }
    }

    static clearData(): void {
        try {
            localStorage.clear();
        } catch (error) {
            console.error(`Error clearing localStorage`, error);
        }
    }
}
