import React, { useEffect, useState } from 'react';
import {IonList, IonItem, IonLabel, IonButton, IonContent} from '@ionic/react';
import { ItemProps } from './ItemProps';
import Item from './Item';
import { getItems, updateItem, newWebSocket } from './itemApi';
import { StorageService } from './storageService';
import { SyncService } from './syncService';

interface ItemListProps {
    onSelectUser: (sender: string | null) => void;
}

const STORAGE_KEY = "messages";

const ItemList: React.FC<ItemListProps> = ({ onSelectUser }) => {
    const [messages, setMessages] = useState<ItemProps[]>([]);
    const [selectedUser, setSelectedUser] = useState<string | null>(null);

    // useEffect(() => {
    //     console.log("Șterg memoria locală doar dacă există mesaje salvate...");
    //     if (localStorage.getItem(STORAGE_KEY)) {
    //         localStorage.clear();
    //         StorageService.clearData && StorageService.clearData();
    //         SyncService.clearQueue();
    //     }
    // }, []);

    useEffect(() => {

        const storedMessages = StorageService.getData<ItemProps[]>(STORAGE_KEY);
        if (storedMessages) {
            setMessages(storedMessages);
        } else {
            getItems().then(fetchedMessages => {
                setMessages(fetchedMessages);
                StorageService.saveData(STORAGE_KEY, fetchedMessages);
            });
        }
        const closeWebSocket = newWebSocket(newMessage => {
            if (!newMessage || !newMessage.id) {
                console.warn("Received invalid message via WebSocket:", newMessage);
                return;
            }

            setMessages(prevMessages => {
                const updatedMessages = [...prevMessages, newMessage];
                StorageService.saveData(STORAGE_KEY, updatedMessages);
                return updatedMessages;
            });
        });

        return () => closeWebSocket();
    }, []);

    useEffect(() => {
        const interval = setInterval(() => {
            SyncService.processQueue();
        }, 5000);

        return () => clearInterval(interval);
    }, []);

    const markAsRead = (id: number) => {
        setMessages(prev => {
            const updatedMessages = prev.map(msg => msg.id === id ? { ...msg, read: true } : msg);
            StorageService.saveData("messages", updatedMessages);
            return updatedMessages;
        });

        const itemToUpdate = messages.find(msg => msg.id === id);
        if (itemToUpdate) {
            updateItem(itemToUpdate).catch(() => {
                console.warn(`Server offline, adding message ${id} to sync queue`);
                SyncService.addToQueue(itemToUpdate);
            });
        }
    };


    const users = messages.reduce((acc, msg) => {
        if (!msg.sender) return acc;

        let user = acc.find(u => u.sender === msg.sender);
        if (!user) {
            user = { sender: msg.sender, unreadCount: 0 };
            acc.push(user);
        }

        if (!msg.read) {
            user.unreadCount++;
        }

        return acc;
    }, [] as { sender: string, unreadCount: number }[]);


    users.sort((a, b) => b.unreadCount - a.unreadCount);

    const filteredMessages = selectedUser
        ? messages.filter(msg => msg.sender === selectedUser).sort((a, b) => b.created - a.created)
        : [];

    return (
        <IonContent>
            {selectedUser && (
                <IonButton onClick={() => setSelectedUser(null)}>Înapoi</IonButton>
            )}
            <IonList>
                {!selectedUser ? (
                    users.map(user => (
                        <IonItem key={user.sender} button onClick={() => setSelectedUser(user.sender)}>
                            <IonLabel>
                                {user.sender} {user.unreadCount > 0 ? `[${user.unreadCount}]` : ''}
                            </IonLabel>
                        </IonItem>
                    ))
                ) : (
                    filteredMessages.map(msg => <Item key={msg.id} item={msg} onRead={markAsRead} />)
                )}
            </IonList>
        </IonContent>
    );
};

export default ItemList;
