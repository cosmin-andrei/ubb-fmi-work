import React, { useContext, useEffect, useState } from 'react';
import { RouteComponentProps } from 'react-router';
import ProjectComponent from './ProjectComponent';
import { getLogger } from '../core';
import { ProjectContext } from './ProjectProvider';
import { motion } from "framer-motion";
import {
  IonContent,
  IonHeader,
  IonList,
  IonLoading,
  IonPage,
  IonTitle,
  IonToolbar,
  IonToast,
  IonFab,
  IonFabButton,
  IonIcon,
  IonButton,
  IonButtons,
  IonInfiniteScroll,
  IonInfiniteScrollContent,
  IonSearchbar,
  IonSelect,
  IonFooter,
  IonSelectOption,
  IonLabel
} from '@ionic/react';

import { add } from 'ionicons/icons';
import { AuthContext } from '../auth';
import { useNetwork } from '../pages/useNetwork';
import { ProjectProps } from './ProjectProps';
import styles from "./styles.module.css";

import { wifi } from "ionicons/icons";

const log = getLogger('ProjectsList');
const projectsPerPage = 3;
const filterValues = ["Active", "Inactive"];

const AnimatedTitle = () => {
  return (
    <motion.div
      initial={{ opacity: 0, y: -20 }}
      animate={{ opacity: 1, y: 0 }}
      transition={{ duration: 0.5 }}
    >
      <IonTitle>Projects</IonTitle>
    </motion.div>
  );
};

export default AnimatedTitle;


export const ProjectsList: React.FC<RouteComponentProps> = ({ history }) => {
  const { projects, fetching, fetchingError, successMessage, closeShowSuccess } = useContext(ProjectContext);
  const { logout } = useContext(AuthContext);
  const [isOpen, setIsOpen] = useState(false);
  const [index, setIndex] = useState<number>(0);
  const [projectsAux, setProjectsAux] = useState<ProjectProps[] | undefined>([]);
  const [more, setHasMore] = useState(true);
  const [searchText, setSearchText] = useState('');
  const [filter, setFilter] = useState<string | undefined>(undefined);
  const {networkStatus} = useNetwork();

  useEffect(() => {
    if (fetching) setIsOpen(true);
    else setIsOpen(false);
  }, [fetching]);

  log('render');
  console.log(projects);

  function handleLogout() {
    logout?.();
    history.push('/login');
  }

  // Pagination
  useEffect(() => {
    fetchData();
  }, [projects]);

  // Searching
  useEffect(() => {
    if (searchText === "") {
      setProjectsAux(projects);
    }
    if (projects && searchText !== "") {
      setProjectsAux(
        projects.filter(project =>
          project.title?.toLowerCase().includes(searchText.toLowerCase())
        )
      );
    }
  }, [searchText]);

  // Filtering
  useEffect(() => {
    if (projects && filter) {
      setProjectsAux(
        projects.filter(project => {
          if (filter === "Active") return project.status === true;
          else return project.status === false;
        })
      );
    }
  }, [filter]);

  function fetchData() {
    if (projects) {
      const newIndex = Math.min(index + projectsPerPage, projects.length);
      if (newIndex >= projects.length) {
        setHasMore(false);
      } else {
        setHasMore(true);
      }
      setProjectsAux(projects.slice(0, newIndex));
      setIndex(newIndex);
    }
  }

  async function searchNext($event: CustomEvent<void>) {
    await fetchData();
    await ($event.target as HTMLIonInfiniteScrollElement).complete();
  }

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <AnimatedTitle  />

          <IonSelect
            className={styles.selectBar}
            slot="end"
            value={filter}
            placeholder="Filter"
            onIonChange={(e) => setFilter(e.detail.value)}
          >
            {filterValues.map((each) => (
              <IonSelectOption key={each} value={each}>
                {each}
              </IonSelectOption>
            ))}
          </IonSelect>
          
          <IonLabel style={{ marginRight: '5px' }} slot="end">
            Connected: <b style={{color:(networkStatus.connected?"green":"red")}}>•</b>        
        </IonLabel>
          
          <IonSearchbar
            className={styles.customSearchBar}
            placeholder="Search by title"
            value={searchText}
            debounce={200}
            onIonInput={(e) => {
              setSearchText(e.detail.value!);
            }}
            slot="secondary"
          />
          <IonButtons slot="end">
            <IonButton onClick={handleLogout}>Logout</IonButton>
          </IonButtons>
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen>
        <IonLoading isOpen={isOpen} message="Fetching projects..." />
        {projectsAux && (
          <IonList>
            {projectsAux.map(project => (
              <ProjectComponent
                key={project._id}
                _id={project._id}
                title={project.title}
                onEdit={id => history.push(`/project/${id}`)}
                description={project.description}
                date={project.date}
                participants={project.participants}
                status={project.status}
                isNotSaved={project.isNotSaved}
              />
            ))}
          </IonList>
        )}
        <IonInfiniteScroll
          threshold="100px"
          disabled={!more}
          onIonInfinite={(e: CustomEvent<void>) => searchNext(e)}
        >
          <IonInfiniteScrollContent loadingText="Loading more projects..." />
        </IonInfiniteScroll>
        {fetchingError && (
          <div>{fetchingError.message || 'Failed to fetch projects'}</div>
        )}
        <IonFab vertical="bottom" horizontal="end" slot="fixed">
          <IonFabButton onClick={() => history.push('/project')}>
            <IonIcon icon={add} />
          </IonFabButton>
        </IonFab>
        <IonToast
          isOpen={!!successMessage}
          message={successMessage}
          position="bottom"
          buttons={[
            {
              text: 'Dismiss',
              role: 'cancel',
              handler: () => {
                console.log('Dismiss clicked');
              },
            },
          ]}
          onDidDismiss={closeShowSuccess}
          duration={5000}
        />

        
      </IonContent>

      <IonFooter>
                <div style={{
                    display: "flex",
                    height: 40,
                    justifyContent: "center",
                    alignItems: "center",
                    gap: 5,
                    backgroundColor: '#000'
                }}>
                    {networkStatus.connected ? <IonIcon icon={wifi} size="large" color="primary"></IonIcon> :
                        <IonIcon icon={wifi} size="large" color="danger"></IonIcon>
                    }
                    <div>Network status: {networkStatus.connected ? "connected" : "no network connection"}</div>
                </div>
            </IonFooter>
    </IonPage>
    
  );
};
