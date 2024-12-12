import React, { useCallback, useContext, useState } from 'react';
import {
  IonButton,
  IonButtons,
  IonContent,
  IonHeader,
  IonInput,
  IonPage,
  IonTitle,
  IonToolbar,
  IonBackButton,
  IonLabel,
  IonDatetime,
  IonCheckbox,
  IonLoading,
  IonToast
} from '@ionic/react';
import { getLogger } from '../core';
import { RouteComponentProps } from 'react-router';
import { ProjectContext } from './ProjectProvider';
import { ProjectProps } from './ProjectProps';
import styles from './styles.module.css';

const log = getLogger('ProjectAdd');

interface ProjectAddProps extends RouteComponentProps<{
  id?: string;
}> {}

export const ProjectAdd: React.FC<ProjectAddProps> = ({ history }) => {
  log("Project add rendered");
  const { addProject, updating, updateError } = useContext(ProjectContext);

  const [title, setTitle] = useState('');
  const [description, setDescription] = useState('');
  const [date, setDate] = useState(new Date());
  const [participants, setParticipants] = useState(0);
  const [status, setStatus] = useState(false);
  const [isNotSaved, setIsNotSaved] = useState(true);
  const [showToast, setShowToast] = useState(false); // Mesaj pentru succes

  const handleAdd = useCallback(() => {
    if (!title || !description) {
      log("Validation failed: Title and description are required.");
      return;
    }

    const newProject: ProjectProps = {
      title,
      description,
      date,
      participants,
      status,
      isNotSaved,
    };

    log("Adding project:", newProject);

    addProject && addProject(newProject)
      .then(() => {
        setIsNotSaved(false);
        setShowToast(true); // Afișează mesajul de succes
        // Resetează formularul
        setTitle('');
        setDescription('');
        setParticipants(0);
        setStatus(false);
        setDate(new Date());
        history.goBack();
      })
      .catch(() => {
        setIsNotSaved(true);
      });
  }, [addProject, title, description, date, participants, status, isNotSaved, history]);

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonButtons slot="start">
            <IonBackButton />
          </IonButtons>
          <IonTitle>Add Project</IonTitle>
          <IonButtons slot="end">
            <IonButton onClick={handleAdd}>Add</IonButton>
          </IonButtons>
        </IonToolbar>
      </IonHeader>
      <IonContent>
        <br />
        <IonLabel><b>Title</b></IonLabel>
        <IonInput
          value={title}
          onIonChange={e => setTitle(e.detail.value || '')}
          placeholder="Enter project title"
        />
        <br />
        <IonLabel><b>Description</b></IonLabel>
        <IonInput
          value={description}
          onIonChange={e => setDescription(e.detail.value || '')}
          placeholder="Enter project description"
        />
        <br />
        <IonLabel><b>Date</b></IonLabel>
        <IonDatetime
          presentation="date"
          value={date.toISOString()}
          onIonChange={e => {
            const value = e.detail.value;
            if (typeof value === 'string') {
              setDate(new Date(Date.parse(value)));
            }
          }}
        />
        <br />
        <IonLabel><b>Status</b></IonLabel>
        <IonCheckbox checked={status} onIonChange={e => setStatus(e.detail.checked)} />
        <br />
        <IonLabel><b>No. Participants</b></IonLabel>
        <IonInput
          type="number"
          value={participants}
          onIonChange={e => setParticipants(Number.parseInt(e.detail.value || '0'))}
        />
        <br />
        {updateError && (
          <div className={styles.errorMessage}>
            {updateError.message || 'Failed to save project'}
          </div>
        )}
        <IonLoading isOpen={updating} />
        <IonToast
          isOpen={showToast}
          message="Project added successfully!"
          duration={2000}
          onDidDismiss={() => setShowToast(false)}
        />
      </IonContent>
    </IonPage>
  );
};
