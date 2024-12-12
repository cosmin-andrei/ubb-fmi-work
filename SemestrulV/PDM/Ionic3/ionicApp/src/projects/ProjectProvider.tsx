import React, { useCallback, useEffect, useReducer, useContext } from 'react';
import PropTypes from 'prop-types';
import { getLogger } from '../core';
import { getAllProjects, updateProjectAPI, createProjectAPI, newWebSocket, deleteProjectAPI } from './ProjectApi';
import { ProjectProps } from './ProjectProps';
import { AuthContext } from '../auth';
import { useNetwork } from '../pages/useNetwork';
import { useIonToast } from "@ionic/react";
import { Preferences } from '@capacitor/preferences';

const log = getLogger('ProjectProvider');

type UpdateProjectFn = (project: ProjectProps) => Promise<any>;
type DeleteProjectFn = (id: string) => Promise<any>;

interface ProjectsState {
    projects?: ProjectProps[];
    fetching: boolean;
    fetchingError?: Error | null;
    updating: boolean,
    updateError?: Error | null,
    updateProject?: UpdateProjectFn,
    addProject?: UpdateProjectFn,
    deleteProject?: DeleteProjectFn;
    successMessage?: string;
    closeShowSuccess?: () => void;
}

interface ActionProps {
    type: string,
    payload?: any,
}

const initialState: ProjectsState = {
    fetching: false,
    updating: false,
};

const FETCH_PROJECTS_STARTED = 'FETCH_PROJECTS_STARTED';
const FETCH_PROJECTS_SUCCEEDED = 'FETCH_PROJECTS_SUCCEEDED';
const FETCH_PROJECTS_FAILED = 'FETCH_PROJECTS_FAILED';
const UPDATE_PROJECT_STARTED = 'UPDATE_PROJECT_STARTED';
const UPDATE_PROJECT_SUCCEDED = 'UPDATE_PROJECT_SUCCEDED';
const UPDATE_PROJECT_FAILED = 'UPDATE_PROJECT_FAILED';
const SHOW_SUCCESS_MESSSAGE = 'SHOW_SUCCESS_MESSAGE';
const HIDE_SUCCESS_MESSSAGE = 'HIDE_SUCCESS_MESSAGE';
const CREATE_PROJECT_STARTED = 'CREATE_PROJECT_STARTED';
const CREATE_PROJECT_SUCCEDED = 'CREATE_PROJECT_SUCCEDED';
const CREATE_PROJECT_FAILED = 'CREATE_PROJECT_FAILED';
const DELETE_PROJECT_STARTED = 'DELETE_PROJECT_STARTED';
const DELETE_PROJECT_SUCCEDED = 'DELETE_PROJECT_SUCCEDED';
const DELETE_PROJECT_FAILED = 'DELETE_PROJECT_FAILED';

const reducer: (state: ProjectsState, action: ActionProps) => ProjectsState
    = (state, { type, payload }) => {
    switch(type){
        case FETCH_PROJECTS_STARTED:
            return { ...state, fetching: true, fetchingError: null };
        case FETCH_PROJECTS_SUCCEEDED:
            return {...state, projects: payload.projects, fetching: false };
        case FETCH_PROJECTS_FAILED:
            return { ...state, fetchingError: payload.error, fetching: false };
        case UPDATE_PROJECT_STARTED:
            return { ...state, updateError: null, updating: true };
        case UPDATE_PROJECT_FAILED:
            return { ...state, updateError: payload.error, updating: false };
        case UPDATE_PROJECT_SUCCEDED:
            const projects = [...(state.projects || [])];
            const project = payload.project;
            const index = projects.findIndex(it => it._id === project._id);
            projects[index] = project;
            return { ...state,  projects, updating: false };
        case CREATE_PROJECT_FAILED:
            console.log(payload.error);
          return { ...state, updateError: payload.error, updating: false };
        case CREATE_PROJECT_STARTED:
          return { ...state, updateError: null, updating: true };
        case CREATE_PROJECT_SUCCEDED:
            const beforeProjects = [...(state.projects || [])];
            const createdProject = payload.project;
            const indexOfAdded = beforeProjects.findIndex(it => it._id === createdProject._id || it.title === createdProject.title);
            if (indexOfAdded === -1) {
                beforeProjects.splice(0, 0, createdProject);
            } else {
                beforeProjects[indexOfAdded] = createdProject;
            }
            return { ...state,  projects: beforeProjects, updating: false, updateError: null };
        case DELETE_PROJECT_FAILED:
              console.log(payload.error);
              return { ...state, updateError: payload.error, updating: false };
        case DELETE_PROJECT_STARTED:
              return { ...state, updateError: null, updating: true };
        case DELETE_PROJECT_SUCCEDED:
                const originalProjects = [...(state.projects || [])];
                const deletedProject = payload.project;
                const indexOfDeleted = originalProjects.findIndex(it => it._id === deletedProject._id);
                if (indexOfDeleted > -1) {
                  originalProjects.splice(indexOfDeleted, 1);
                }
                return { ...state,  projects: originalProjects, updating: false };
        case SHOW_SUCCESS_MESSSAGE:
            const allProjects = [...(state.projects || [])];
            const updatedProject = payload.updatedProject;
            const indexOfProject = allProjects.findIndex(it => it._id === updatedProject._id);
            allProjects[indexOfProject] = updatedProject;
            return {...state, projects: allProjects, successMessage: payload.successMessage }
        case HIDE_SUCCESS_MESSSAGE:
            return {...state, successMessage: payload }
        default:
            return state;
    }
};

export const ProjectContext = React.createContext(initialState);

interface ProjectProviderProps {
    children: PropTypes.ReactNodeLike,
}

export const ProjectProvider: React.FC<ProjectProviderProps> = ({ children }) => {
    const [state, dispatch] = useReducer(reducer, initialState);
    const { projects, fetching, fetchingError, updating, updateError, successMessage } = state;
    const { token } = useContext(AuthContext);
    const { networkStatus } = useNetwork();
    const [toast] = useIonToast();

    useEffect(getItemsEffect, [token]);
    useEffect(wsEffect, [token]);
    useEffect(executePendingOperations, [networkStatus.connected, token, toast]);

    const updateProject = useCallback<UpdateProjectFn>(updateProjectCallback, [token]);
    const addProject = useCallback<UpdateProjectFn>(addProjectCallback, [token]);
    const deleteProject = useCallback<DeleteProjectFn>(deleteProjectCallback, [token]);

    log('returns');

    function getItemsEffect() {
        let canceled = false;
        fetchItems();
        return () => {
            canceled = true;
        }

        async function fetchItems() {
          if(!token?.trim()){
            return;
          }

            try{
                log('fetchProjects started');
                dispatch({ type: FETCH_PROJECTS_STARTED });
                const projects = await getAllProjects(token);
                log('fetchItems succeeded');
                if (!canceled) {
                dispatch({ type: FETCH_PROJECTS_SUCCEEDED, payload: { projects } });
                }
            } catch (error) {
                log('fetchItems failed');
                if (!canceled) {
                    dispatch({ type: FETCH_PROJECTS_FAILED, payload: { error } });
                }
            }
        }
    }

    async function updateProjectCallback(project: ProjectProps) {
        try {
          log('updateProject started');
          dispatch({ type: UPDATE_PROJECT_STARTED });
          const updatedProject = await updateProjectAPI(token, project);
          log('saveProject succeeded');
          dispatch({ type: UPDATE_PROJECT_SUCCEDED, payload: { project: updatedProject } });
        } catch (error: any) {
          log('updateProject failed');
          project.isNotSaved = true;
          await Preferences.set({
            key: `upd-${project.title}`,
            value: JSON.stringify({token, project })
          });
          dispatch({ type: UPDATE_PROJECT_SUCCEDED, payload: { project: project } });
          toast("You are offline... Updating project locally!", 3000);
          if(error.toJSON().message === 'Network Error')
            dispatch({ type: UPDATE_PROJECT_FAILED, payload: { error: new Error(error.response) } });
        }
    }

    async function addProjectCallback(project: ProjectProps){
        try{
          log('addProject started');
          dispatch({ type: CREATE_PROJECT_STARTED });
          const addedProject = await createProjectAPI(token, project);
          log('saveProject succeeded');
          dispatch({ type: CREATE_PROJECT_SUCCEDED, payload: { project: addedProject } });
        }catch(error: any){
          log('addProject failed');
          const { keys } = await Preferences.keys();
          const matchingKeys = keys.filter(key => key.startsWith('sav-'));
          const numberOfItems = matchingKeys.length + 1;
          project._id = numberOfItems.toString();
          project.isNotSaved = true;
          await Preferences.set({
            key: `sav-${project.title}`,
            value: JSON.stringify({token, project })
          });
          dispatch({ type: CREATE_PROJECT_SUCCEDED, payload: { project: project } });
          toast("You are offline... Saving project locally!", 3000);
          if(error.toJSON().message === 'Network Error')
            dispatch({ type: CREATE_PROJECT_FAILED, payload: { error: new Error(error.response || 'Network error') } });
        }
    }

    async function deleteProjectCallback(id: string){
        try{
          log('deleteProject started');
          dispatch({ type: DELETE_PROJECT_STARTED });
          const deletedProject = await deleteProjectAPI(token, id);
          log('deleteProject succeeded');
          dispatch({ type: DELETE_PROJECT_SUCCEDED, payload: { project: deletedProject } });
        }catch(error: any){
          log('deleteProject failed');
          dispatch({ type: DELETE_PROJECT_FAILED, payload: { error: new Error(error.response.data.message) } });
        }
    }

    function executePendingOperations(){
      async function helperMethod(){
          if(networkStatus.connected && token?.trim()){
              log('executing pending operations')
              const { keys } = await Preferences.keys();
              for(const key of keys) {
                  if(key.startsWith("sav-")){
                      const res = await Preferences.get({key: key});
                      if (typeof res.value === "string") {
                          const value = JSON.parse(res.value);
                          value.project._id=undefined;
                          log('creating item from pending', value);
                          await addProjectCallback(value.project);
                          await Preferences.remove({key: key});
                      }
                  }
              }
              for(const key of keys) {
                if(key.startsWith("upd-")){
                    const res = await Preferences.get({key: key});
                    if (typeof res.value === "string") {
                        const value = JSON.parse(res.value);
                        log('updating item from pending', value);
                        await updateProjectCallback(value.project);
                        await Preferences.remove({key: key});
                    }
                }
            }
          }
      }
      helperMethod();
  }

    function wsEffect() {
        let canceled = false;
        log('wsEffect - connecting');
        let closeWebSocket: () => void;
        if(token?.trim()){
          closeWebSocket = newWebSocket(token, message => {
            if (canceled) {
              return;
            }
            const { event, payload } = message;
            log(`ws message, item ${event}`);
            if (event === 'updated') {
              dispatch({ type: SHOW_SUCCESS_MESSSAGE, payload: {successMessage: payload.successMessage, updatedProject: payload.updatedProject } });
            }
            else if(event == 'created'){
              dispatch({ type: CREATE_PROJECT_SUCCEDED, payload: { project: payload.updatedProject } });
            }
            else if(event === 'deleted'){
              dispatch({ type: DELETE_PROJECT_SUCCEDED, payload: { project: payload.updatedProject } });
            }
          });
        }
        return () => {
          log('wsEffect - disconnecting');
          canceled = true;
          closeWebSocket?.();
        }
    }

    function closeShowSuccess(){
        dispatch({ type: HIDE_SUCCESS_MESSSAGE, payload: null });
    }

    const value = { projects, fetching, fetchingError, updating, updateError, updateProject, addProject, deleteProject, successMessage, closeShowSuccess };

    return (
        <ProjectContext.Provider value={value}>
            {children}
        </ProjectContext.Provider>
    );
};

export default ProjectProvider;
