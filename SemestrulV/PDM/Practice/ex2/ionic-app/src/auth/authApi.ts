import axios from 'axios';
import { baseUrl, config, withLogs } from '../core';

const authUrl = `http://${baseUrl}/auth`;

export interface AuthProps {
    token: string;
    questionIds: number[];
}

export const login: (id: string) => Promise<AuthProps> = (id) => {
    return withLogs(axios.post(authUrl, { id }, config), 'login');
};

