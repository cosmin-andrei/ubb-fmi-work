import React, { useState, useEffect, useCallback } from 'react';
import {
    IonPage,
    IonHeader,
    IonToolbar,
    IonTitle,
    IonContent,
    IonLoading,
    IonList,
    IonItem,
    IonLabel,
    IonInput,
    IonButton,
    IonToast,
    IonItemDivider
} from '@ionic/react';
import axios from 'axios';
import { useHistory } from 'react-router-dom';
import { Parcare } from '../components/parcare';

const API_URL = 'http://localhost:3000';

const Home: React.FC = () => {
    const [parcari, setParcari] = useState<Parcare[]>([]);
    const [loading, setLoading] = useState<boolean>(false);
    const [updateLoadingIds, setUpdateLoadingIds] = useState<number[]>([]);
    const [error, setError] = useState<string>('');
    const [wsError, setWsError] = useState<string>('');
    const [search, setSearch] = useState<string>('');
    const [expandedId, setExpandedId] = useState<number | null>(null);
    const [retryAction, setRetryAction] = useState<() => void>(() => {});
    const username = localStorage.getItem('username') || '';
    const history = useHistory();

    const saveParcariCache = (data: Parcare[]) => {
        localStorage.setItem('parcariCache', JSON.stringify(data));
    };

    const loadParcariCache = (): Parcare[] => {
        const cached = localStorage.getItem('parcariCache');
        return cached ? JSON.parse(cached) : [];
    };

    const fetchParcari = useCallback(async () => {
        setLoading(true);
        try {
            const res = await axios.get<Parcare[]>(`${API_URL}/space`);
            setParcari(res.data);
            saveParcariCache(res.data);
            setError('');
        } catch (err) {
            setError('Eroare la descărcarea datelor de parcare.');
            const cached = loadParcariCache();
            if (cached.length) {
                setParcari(cached);
            }
            setRetryAction(() => fetchParcari);
        } finally {
            setLoading(false);
        }
    }, []);

    useEffect(() => {
        fetchParcari();
    }, [fetchParcari]);

    useEffect(() => {
        let socket: WebSocket;
        let connectInterval: any;
        const connect = () => {
            socket = new WebSocket('ws://localhost:3000');
            socket.onopen = () => {
                console.log('WebSocket conectat');
                setWsError('');
                if (connectInterval) clearInterval(connectInterval);
            };
            socket.onmessage = event => {
                try {
                    const data: Parcare = JSON.parse(event.data);
                    setParcari(prevParcari => {
                        const updated = prevParcari.map(p => (p.id === data.id ? data : p));
                        saveParcariCache(updated);
                        return updated;
                    });
                } catch (err) {
                    console.error('Eroare la parsarea mesajului WS', err);
                }
            };
            socket.onclose = e => {
                console.log(`WebSocket închis. Cod: ${e.code}. Se încearcă reconectarea...`);
                setWsError('Conexiune WS pierdută. Se reconectează...');
                connectInterval = setTimeout(check, 3000);
            };
            socket.onerror = err => {
                console.error('WebSocket eroare: ', err);
                socket.close();
            };
        };
        const check = () => {
            if (!socket || socket.readyState === WebSocket.CLOSED) connect();
        };
        connect();
        return () => {
            if (socket) socket.close();
            if (connectInterval) clearInterval(connectInterval);
        };
    }, []);

    const updateParcare = async (parcare: Parcare, newStatus: 'taken' | 'free') => {
        const previousParcare = parcare;
        const updatedParcare: Parcare = { ...parcare, takenBy: newStatus === 'taken' ? username : '' };
        setParcari(prev => prev.map(p => (p.id === parcare.id ? updatedParcare : p)));
        saveParcariCache(parcari.map(p => (p.id === parcare.id ? updatedParcare : p)));
        setUpdateLoadingIds(prev => [...prev, parcare.id]);
        try {
            const payload = { ...parcare, status: newStatus, takenBy: newStatus === 'taken' ? username : '' };
            const res = await axios.put<Parcare>(`${API_URL}/space/${parcare.id}`, payload);
            setParcari(prev => prev.map(p => (p.id === res.data.id ? res.data : p)));
            saveParcariCache(parcari.map(p => (p.id === res.data.id ? res.data : p)));
        } catch (err) {
            setError('Eroare la actualizarea locului de parcare.');
            setParcari(prev => prev.map(p => (p.id === previousParcare.id ? previousParcare : p)));
            setRetryAction(() => () => updateParcare(parcare, newStatus));
        } finally {
            setUpdateLoadingIds(prev => prev.filter(id => id !== parcare.id));
        }
    };

    const filteredParcari = parcari.filter(p => p.number.toLowerCase().includes(search.toLowerCase()));
    const handleItemClick = (id: number) => {
        setExpandedId(expandedId === id ? null : id);
    };

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Locuri de parcare</IonTitle>
                </IonToolbar>
            </IonHeader>
            <IonContent className="ion-padding">
                <IonItem>
                    <IonLabel position="stacked">Caută după număr</IonLabel>
                    <IonInput value={search} placeholder="ex. s12" onIonChange={e => setSearch(e.detail.value!)} />
                </IonItem>
                <IonLoading isOpen={loading} message={'Se descarcă datele...'} />
                {error && (
                    <>
                        <IonItemDivider color="danger">
                            <IonLabel>{error}</IonLabel>
                        </IonItemDivider>
                        <IonButton expand="block" onClick={retryAction}>
                            Retry
                        </IonButton>
                    </>
                )}
                <IonList>
                    {filteredParcari.map(parcare => {
                        const itemStyle: React.CSSProperties = {
                            backgroundColor: parcare.takenBy === '' ? '#d4edda' : parcare.takenBy === username ? '#fff3cd' : '#f8d7da',
                            marginBottom: '10px',
                            borderRadius: '4px',
                            padding: '10px'
                        };
                        const isExpanded = expandedId === parcare.id;
                        return (
                            <div key={parcare.id} style={itemStyle}>
                                <IonItem button onClick={() => handleItemClick(parcare.id)}>
                                    <IonLabel>
                                        <h2>{parcare.number}</h2>
                                        <p>{parcare.takenBy ? `Ocupat de ${parcare.takenBy}` : 'Liber'}</p>
                                    </IonLabel>
                                </IonItem>
                                {isExpanded && (
                                    <div style={{ marginTop: '10px' }}>
                                        {updateLoadingIds.includes(parcare.id) ? (
                                            <IonLoading isOpen={true} message={'Se actualizează...'} />
                                        ) : (
                                            <>
                                                {parcare.takenBy === '' && (
                                                    <IonButton expand="block" onClick={() => updateParcare(parcare, 'taken')}>
                                                        Take
                                                    </IonButton>
                                                )}
                                                {parcare.takenBy === username && (
                                                    <IonButton expand="block" onClick={() => updateParcare(parcare, 'free')}>
                                                        Release
                                                    </IonButton>
                                                )}
                                            </>
                                        )}
                                    </div>
                                )}
                            </div>
                        );
                    })}
                </IonList>
                <IonToast isOpen={!!wsError} message={wsError} duration={2000} onDidDismiss={() => setWsError('')} />
            </IonContent>
        </IonPage>
    );
};

export default Home;
