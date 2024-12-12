import axios from "axios";
import { getLogger, authConfig, baseUrl, withLogs } from "../core";
import { ProjectProps } from "./ProjectProps";
import { Preferences } from "@capacitor/preferences";

const log = getLogger('projectLogger');

const projectsUrl = `http://${baseUrl}/api/project`;

export const getAllProjects: (token: string) => Promise<ProjectProps[]> = async (token) => {
    return withLogs(axios.get(projectsUrl, authConfig(token)), 'getAllProjects');
};

export const updateProjectAPI: (token: string, project: ProjectProps) => Promise<ProjectProps> = async (token, project) => {
  return withLogs(axios.put(`${projectsUrl}/${project._id}`, project, authConfig(token)), 'updateProject');
};


export const createProjectAPI: (token: string, project: ProjectProps) => Promise<ProjectProps[]> = async (token, project) => {
    return withLogs(axios.post(projectsUrl, project, authConfig(token)), 'createProject');
};

export const deleteProjectAPI: (token: string, id: string) => Promise<ProjectProps[]> = async (token, id) => {
    return withLogs(axios.delete(`${projectsUrl}/${id}`, authConfig(token)), 'deleteProject');
};

interface MessageData {
  event: string;
  payload: {
    successMessage: string;
    updatedProject: ProjectProps[];
  };
}

export const newWebSocket = (token: string, onMessage: (data: MessageData) => void) => {
  const ws = new WebSocket(`ws://${baseUrl}`)
  ws.onopen = () => {
    log('web socket onopen');
    ws.send(JSON.stringify({type: 'authorization', payload :{token}}));
  };
  ws.onclose = () => {
    log('web socket onclose');
  };
  ws.onerror = error => {
    log('web socket onerror', error);
  };
  ws.onmessage = messageEvent => {
    log('web socket onmessage');
    console.log(messageEvent.data);
    onMessage(JSON.parse(messageEvent.data));
  };
  return () => {
    ws.close();
  }
}
