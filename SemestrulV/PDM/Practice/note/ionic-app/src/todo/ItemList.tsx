import React, { useEffect, useState, useRef, useCallback } from 'react';
import { IonList, IonButton, IonContent, IonAlert, IonCard, IonCardHeader, IonCardTitle, IonCardContent, IonSpinner, IonRow, IonCol } from '@ionic/react';
import { ItemProps } from './ItemProps';
import { getItems, deleteItem } from './itemApi';
import { StorageService } from './storageService';
import { SyncService } from './syncService';

const STORAGE_KEY = "items";
const LAST_MODIFIED_KEY = "lastModified";

const ItemList: React.FC = () => {
    const [items, setItems] = useState<ItemProps[]>([]);
    const [page, setPage] = useState(1);
    const [hasMore, setHasMore] = useState(true);
    const [showConfirm, setShowConfirm] = useState<{ show: boolean, id?: number }>({ show: false });
    const [isLoading, setIsLoading] = useState(false);
    const loadMoreRef = useRef<HTMLDivElement | null>(null);

    useEffect(() => {
        initializeData();
    }, []);

    const initializeData = async () => {
        console.log("Reset old cache...");
        StorageService.removeData(LAST_MODIFIED_KEY);
        StorageService.removeData(STORAGE_KEY);

        console.log("First page...");
        const response = await getItems(1);

        if (response.notes.length > 0) {
            console.log("Save page in cache...");
            StorageService.saveData(STORAGE_KEY, response.notes);
            setItems(response.notes);
            setPage(2);
            setHasMore(response.more);
        } else {
            console.log("No data found.");
            setHasMore(false);
        }
    };

    const fetchNextPage = useCallback(async () => {
        if (isLoading || !hasMore) return;

        setIsLoading(true);
        console.log(`Download page ${page}...`);
        const response = await getItems(page);

        if (response.notes.length > 0) {
            setItems(prevItems => {
                const newItems = [...prevItems, ...response.notes].reduce((unique, item) => {
                    return unique.some(i => i.id === item.id) ? unique : [...unique, item];
                }, [] as ItemProps[]);
                StorageService.saveData(STORAGE_KEY, newItems);
                return newItems;
            });
            setPage(prevPage => prevPage + 1);
        } else {
            setHasMore(false);
        }
        setIsLoading(false);
    }, [page, isLoading, hasMore]);

    useEffect(() => {
        if (!loadMoreRef.current) return;

        const observer = new IntersectionObserver(
            (entries) => {
                if (entries[0].isIntersecting) {
                    fetchNextPage();
                }
            },
            { threshold: 1.0 }
        );

        observer.observe(loadMoreRef.current);

        return () => observer.disconnect();
    }, [fetchNextPage]);

    const handleDelete = async (id: number) => {
        try {
            await deleteItem(id);
            setItems(prevItems => {
                const updatedItems = prevItems.filter(item => item.id !== id);
                StorageService.saveData(STORAGE_KEY, updatedItems);
                return updatedItems;
            });
        } catch (error) {
            console.error("Ștergerea a eșuat, adăugăm în coada de sincronizare", error);
            SyncService.addToQueue({ id, text: "[În așteptare ștergere]", date: new Date().toISOString(), deleted: true });

            setItems(prevItems =>
                prevItems.map(n => (n.id === id ? { ...n, text: "[În așteptare ștergere]" } : n))
            );
        }
    };

    useEffect(() => {
        const ws = new WebSocket(`ws://localhost:3000`);

        ws.onmessage = (event) => {
            const data = JSON.parse(event.data);

            if (data.event === 'deleted') {
                setItems(prevItems => {
                    const updatedItems = prevItems.filter(item => item.id !== data.note.id);
                    StorageService.saveData(STORAGE_KEY, updatedItems);
                    return updatedItems;
                });
            } else if (data.event === 'inserted') {
                setItems(prevItems => {
                    const updatedItems = [...prevItems];
                    const existingIndex = updatedItems.findIndex(item => item.id === data.note.id);

                    if (existingIndex === -1) {
                        updatedItems.push(data.note);
                    } else {
                        updatedItems[existingIndex] = data.note;
                    }

                    StorageService.saveData(STORAGE_KEY, updatedItems);
                    return updatedItems;
                });
            }
        };

        SyncService.startSyncInterval();

        return () => {
            ws.close();
        };
    }, []);

    return (
        <IonContent>
            <IonList>
                {items.map(item => (
                    <IonCard key={item.id} className="ion-padding">
                        <IonCardHeader>
                            <IonRow className="ion-align-items-center">
                                <IonCol size="10">
                                    <IonCardTitle>{item.text}</IonCardTitle>
                                </IonCol>
                                <IonCol size="2" className="ion-text-right">
                                    <IonButton
                                        fill="clear"
                                        color="danger"
                                        onClick={() => setShowConfirm({ show: true, id: item.id })}
                                    >
                                        🗑️
                                    </IonButton>
                                </IonCol>
                            </IonRow>
                        </IonCardHeader>
                        <IonCardContent>
                            <p><strong>Data:</strong> {new Date(item.date).toLocaleString()}</p>
                        </IonCardContent>
                    </IonCard>
                ))}
            </IonList>

            {isLoading && (
                <div className="ion-text-center ion-padding">
                    <IonSpinner />
                </div>
            )}

            <div ref={loadMoreRef} style={{ height: "10px" }} />

            <IonAlert
                isOpen={showConfirm.show}
                onDidDismiss={() => setShowConfirm({ show: false })}
                header={'Confirmare'}
                message={'Sigur doriți să ștergeți această notă?'}
                buttons={[
                    { text: 'Anulează', role: 'cancel' },
                    {
                        text: 'Șterge',
                        handler: () => {
                            if (showConfirm.id) handleDelete(showConfirm.id);
                            return true;
                        }
                    }
                ]}
            />
        </IonContent>
    );
};

export default ItemList;
