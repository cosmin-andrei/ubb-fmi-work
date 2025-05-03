import React, { useState, useEffect } from 'react';
import { IonPage, IonContent, IonHeader, IonTitle, IonToolbar, IonInput, IonButton, IonItem, IonLabel } from '@ionic/react';
import { useHistory } from 'react-router-dom';

const Auth: React.FC = () => {
    const [username, setUsername] = useState('');
    const history = useHistory();

    useEffect(() => {
        const storedUser = localStorage.getItem('username');
        if (storedUser) {
            history.replace('/home');
        }
    }, [history]);

    const handleNext = () => {
        if (username.trim()) {
            localStorage.setItem('username', username.trim());
            history.push('/home');
        }
    };

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Autentificare</IonTitle>
                </IonToolbar>
            </IonHeader>
            <IonContent className="ion-padding">
                <IonItem>
                    <IonLabel position="stacked">Nume utilizator</IonLabel>
                    <IonInput
                        value={username}
                        placeholder="Introdu username-ul"
                        onIonChange={e => setUsername(e.detail.value!)}
                    />
                </IonItem>
                <IonButton expand="block" onClick={handleNext} style={{ marginTop: '20px' }}>
                    Next
                </IonButton>
            </IonContent>
        </IonPage>
    );
};

export default Auth;
