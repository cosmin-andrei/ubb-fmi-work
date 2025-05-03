import React, { useEffect, useState, useCallback } from 'react';
import { IonList, IonItem, IonLabel, IonSpinner, IonButton } from '@ionic/react';
import { io, Socket } from 'socket.io-client';
import { Message } from '../pages/types';

const MessagesList: React.FC = () => {
    const [socket, setSocket] = useState<Socket | null>(null);
    const [messages, setMessages] = useState<Message[]>([]);
    const [loading, setLoading] = useState<boolean>(true);
    const [selectedUser, setSelectedUser] = useState<string | null>(null);
    const [highlightedMessages, setHighlightedMessages] = useState<Set<number>>(new Set());
    const [unreadMessages, setUnreadMessages] = useState<{ [key: string]: number }>({});

    const updateUnreadCount = useCallback((currentMessages: Message[]) => {
        const counts: { [key: string]: number } = {};
        currentMessages.forEach((msg) => {
            if (!msg.read) {
                counts[msg.sender] = (counts[msg.sender] || 0) + 1;
            }
        });
        setUnreadMessages(counts);
    }, []);

    // Initialize socket connection
    useEffect(() => {
        const newSocket = io('http://localhost:3000');
        setSocket(newSocket);

        return () => {
            newSocket.close();
        };
    }, []);

    // Handle new messages
    useEffect(() => {
        if (!socket) return;

        const handleNewMessage = (newMessage: Message) => {
            setMessages(prevMessages => {
                const updatedMessages = [...prevMessages, newMessage];
                updateUnreadCount(updatedMessages);
                return updatedMessages;
            });

            if (selectedUser === newMessage.sender) {
                highlightMessage(newMessage.id);
                setTimeout(() => markMessageAsRead(newMessage), 1000);
            }
        };

        socket.on('newMessage', handleNewMessage);

        return () => {
            socket.off('newMessage', handleNewMessage);
        };
    }, [socket, selectedUser, updateUnreadCount]);

    // Initial message fetch
    useEffect(() => {
        fetchMessages();
    }, [updateUnreadCount]);

    const fetchMessages = async () => {
        try {
            const response = await fetch('http://localhost:3000/message');
            const data: Message[] = await response.json();
            setMessages(data);
            updateUnreadCount(data);
        } catch (error) {
            console.error('Error fetching messages:', error);
        } finally {
            setLoading(false);
        }
    };

    const highlightMessage = (messageId: number) => {
        setHighlightedMessages(prev => new Set(prev).add(messageId));
        setTimeout(() => {
            setHighlightedMessages(prev => {
                const updated = new Set(prev);
                updated.delete(messageId);
                return updated;
            });
        }, 1000);
    };

    const markMessageAsRead = async (message: Message) => {
        try {
            await fetch(`http://localhost:3000/message/${message.id}`, {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ ...message, read: true }),
            });

            setMessages(prevMessages => {
                const updatedMessages = prevMessages.map(msg =>
                    msg.id === message.id ? { ...msg, read: true } : msg
                );
                updateUnreadCount(updatedMessages);
                return updatedMessages;
            });
        } catch (error) {
            console.error('Error marking message as read:', error);
        }
    };

    const getSortedUsersWithUnreadCount = () => {
        const usersSet = new Set<string>(messages.map(msg => msg.sender));
        const users = Array.from(usersSet);
        users.sort((a, b) => {
            const countA = unreadMessages[a] || 0;
            const countB = unreadMessages[b] || 0;
            if (countA !== countB) return countB - countA;
            const lastA = messages
                .filter(msg => msg.sender === a)
                .reduce((max, msg) => Math.max(max, msg.created), 0);
            const lastB = messages
                .filter(msg => msg.sender === b)
                .reduce((max, msg) => Math.max(max, msg.created), 0);
            return lastB - lastA;
        });
        return users;
    };

    const getMessagesForSelectedUser = () => {
        return messages
            .filter(msg => msg.sender === selectedUser)
            .sort((a, b) => a.created - b.created);
    };

    const handleUserSelection = (user: string) => {
        setSelectedUser(user);
        const unreadFromUser = messages.filter(
            msg => msg.sender === user && !msg.read
        );
        unreadFromUser.forEach(msg => {
            highlightMessage(msg.id);
            setTimeout(() => markMessageAsRead(msg), 1000);
        });
    };

    return (
        <>
            {loading ? (
                <IonSpinner name="crescent" />
            ) : selectedUser ? (
                <>
                    <IonButton onClick={() => setSelectedUser(null)}>← Back</IonButton>
                    <IonList>
                        {getMessagesForSelectedUser().map(msg => (
                            <IonItem key={msg.id}>
                                <IonLabel style={{ fontWeight: highlightedMessages.has(msg.id) ? 'bold' : 'normal' }}>
                                    {msg.text}
                                </IonLabel>
                            </IonItem>
                        ))}
                    </IonList>
                </>
            ) : (
                <IonList>
                    {getSortedUsersWithUnreadCount().map((sender, index) => (
                        <IonItem key={index} button onClick={() => handleUserSelection(sender)}>
                            <IonLabel>
                                {sender} {unreadMessages[sender] ? `[${unreadMessages[sender]}]` : ''}
                            </IonLabel>
                        </IonItem>
                    ))}
                </IonList>
            )}
        </>
    );
};

export default MessagesList;