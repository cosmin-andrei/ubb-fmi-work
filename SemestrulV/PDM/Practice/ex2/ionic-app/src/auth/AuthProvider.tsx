import React, { ReactNode, useCallback, useEffect, useState } from 'react';
import { getLogger } from '../core';
import { login as loginApi } from './authApi';

const log = getLogger('AuthProvider');

type LoginFn = (id?: string) => void;

export interface AuthState {
    authenticationError: Error | null;
    isAuthenticated: boolean;
    isAuthenticating: boolean;
    login?: LoginFn;
    pendingAuthentication?: boolean;
    id?: string;
    token: string;
    questionIds?: number[];
}

const initialState: AuthState = {
    isAuthenticated: false,
    isAuthenticating: false,
    authenticationError: null,
    pendingAuthentication: false,
    token: '',
    questionIds: [],
};

export const AuthContext = React.createContext<AuthState>(initialState);

interface AuthProviderProps {
    children: ReactNode,
}

export const AuthProvider: React.FC<AuthProviderProps> = ({ children }) => {
    const [state, setState] = useState<AuthState>(initialState);
    const { isAuthenticated, isAuthenticating, authenticationError, pendingAuthentication, token, questionIds } = state;

    const login = useCallback<LoginFn>((id?: string) => {
        log('login');
        setState(prevState => ({
            ...prevState,
            authenticationError: null,
            pendingAuthentication: true,
            id,
        }));
    }, []);

    useEffect(() => {
        let canceled = false;
        if (pendingAuthentication && state.id) {
            (async () => {
                try {
                    log('authenticate...');
                    setState(prevState => ({
                        ...prevState,
                        isAuthenticating: true,
                    }));
                    const { token, questionIds } = await loginApi(state.id ?? '');
                    if (canceled) return;
                    log('authenticate succeeded');

                    localStorage.setItem('token', token);
                    localStorage.setItem('questionIds', JSON.stringify(questionIds));

                    setState(prevState => ({
                        ...prevState,
                        token,
                        questionIds,
                        pendingAuthentication: false,
                        isAuthenticated: true,
                        isAuthenticating: false,
                    }));
                } catch (error) {
                    if (canceled) return;
                    log('authenticate failed');
                    setState(prevState => ({
                        ...prevState,
                        authenticationError: error as Error,
                        pendingAuthentication: false,
                        isAuthenticating: false,
                    }));
                }
            })();
        }
        return () => { canceled = true; };
    }, [pendingAuthentication, state.id]);

    const value = { isAuthenticated, login, isAuthenticating, authenticationError, token, questionIds };
    log('render');

    return (
        <AuthContext.Provider value={value}>
            {children}
        </AuthContext.Provider>
    );
};
