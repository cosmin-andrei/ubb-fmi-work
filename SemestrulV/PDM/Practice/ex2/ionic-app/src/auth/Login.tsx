import React, { useCallback, useContext, useEffect, useState } from 'react';
import { RouteComponentProps } from 'react-router';
import { IonButton, IonContent, IonHeader, IonInput, IonLoading, IonPage, IonTitle, IonToolbar } from '@ionic/react';
import { AuthContext } from './AuthProvider';
import { getLogger } from '../core';

const log = getLogger('Login');

interface LoginState {
    username?: string;
}

export const Login: React.FC<RouteComponentProps> = ({ history }) => {
    const { isAuthenticated, isAuthenticating, login, authenticationError } = useContext(AuthContext);
    const [state, setState] = useState<LoginState>({});
    const { username } = state;

    const handleUsernameChange = useCallback((e: any) => {
        setState(prevState => ({
            ...prevState,
            username: e.detail.value || ''
        }));
    }, []);

    const handleLogin = useCallback(() => {
        log('handleLogin...');
        if (username) {
            login?.(username);
        }
    }, [username]);


    useEffect(() => {
        if (isAuthenticated) {
            log('redirecting to home');
            history.push('/');
        }
    }, [isAuthenticated, history]);

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Login</IonTitle>
                </IonToolbar>
            </IonHeader>
            <IonContent>
                <IonInput
                    placeholder="Username"
                    value={username}
                    onIonChange={handleUsernameChange} />
                <IonLoading isOpen={isAuthenticating} />
                {authenticationError && (
                    <div>{typeof authenticationError === 'string' ? authenticationError : authenticationError.message || 'Failed to authenticate'}</div>
                )}
                <IonButton onClick={handleLogin}>Login</IonButton>
            </IonContent>
        </IonPage>
    );
};
