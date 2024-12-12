import React, { useCallback, useContext, useEffect, useState } from 'react';
import {
  IonButton, IonButtons, IonContent, IonHeader, IonInput, IonLoading, IonPage,
  IonTitle, IonToolbar, IonBackButton, IonLabel, IonDatetime, IonCheckbox,
  IonFab, IonFabButton, IonIcon, IonImg, IonModal, createAnimation
} from '@ionic/react';
import { getLogger } from '../core';
import { RouteComponentProps } from 'react-router';
import { ProjectContext } from './ProjectProvider';
import { ProjectProps } from './ProjectProps';
import styles from './styles.module.css';

import { Photo, usePhotoGallery } from "../pages/usePhotoGallery";
import { MyMap } from "../pages/MyMap";
import { camera, trash, map } from "ionicons/icons";

const log = getLogger('EditLogger');

interface ProjectEditProps extends RouteComponentProps<{
  id?: string;
}> {}

export const ProjectEdit: React.FC<ProjectEditProps> = ({ history, match }) => {
  const { projects, updating, updateError, updateProject } = useContext(ProjectContext);
  const [title, setTitle] = useState('');
  const [description, setDescription] = useState('');
  const [date, setDate] = useState<Date>(new Date());
  const [participants, setParticipants] = useState(0);
  const [status, setStatus] = useState(false);
  const [projectToUpdate, setProjectToUpdate] = useState<ProjectProps>();

  const { takePhoto } = usePhotoGallery();
  const [webViewPath, setWebViewPath] = useState('');
  const [currentLatitude, setCurrentLatitude] = useState<number | undefined>(undefined);
  const [currentLongitude, setCurrentLongitude] = useState<number | undefined>(undefined);
  const [showMapModal, setShowMapModal] = useState(false);

  useEffect(() => {
    const routeId = match.params.id || '';
    const project = projects?.find(it => it._id === routeId);

    if (project) {
      setProjectToUpdate(project);
      setTitle(project.title);
      setDescription(project.description || '');
      setDate(new Date(project.date || Date.now()));
      setParticipants(project.participants || 0);
      setStatus(project.status || false);
      setWebViewPath(project.photo || "");
      setCurrentLatitude(project.lat || 0);
      setCurrentLongitude(project.lng || 0);
      log("Project loaded:", project);
    } else {
      log("Project not found:", routeId);
    }
  }, [match.params.id, projects]);

  const handleUpdate = useCallback(() => {
    if (!updateProject) {
      console.error("Update function not available");
      return;
    }

    const editedProject: ProjectProps = {
      ...projectToUpdate,
      title,
      description,
      date,
      participants,
      status,
      isNotSaved: projectToUpdate?.isNotSaved ?? false,
      photo: webViewPath,
      lat: currentLatitude,
      lng: currentLongitude
    };

    updateProject(editedProject)
      .then(() => {
        history.goBack();
      })
      .catch(error => {
        console.error("Error updating project:", error);
      });
  }, [
    projectToUpdate, updateProject, title, description, date,
    participants, status, webViewPath, currentLatitude, currentLongitude, history
  ]);

  const enterAnimation = (baseEl: HTMLElement) => {
    const root = baseEl.shadowRoot!;
    const backdropAnimation = createAnimation()
      .addElement(root.querySelector('ion-backdrop')!)
      .fromTo('opacity', '0.01', 'var(--backdrop-opacity)');

    const wrapperAnimation = createAnimation()
      .addElement(root.querySelector('.modal-wrapper')!)
      .keyframes([
        { offset: 0, opacity: '0', transform: 'scale(0)' },
        { offset: 1, opacity: '1', transform: 'scale(1)' },
      ]);

    return createAnimation()
      .addElement(baseEl)
      .easing('ease-out')
      .duration(500)
      .addAnimation([backdropAnimation, wrapperAnimation]);
  };

  const leaveAnimation = (baseEl: HTMLElement) => {
    return enterAnimation(baseEl).direction('reverse');
  };

  const handlePhotoChange = async () => {
    const image = await takePhoto();
    setWebViewPath(image || '');
  };

  const handleDeletePhoto = () => {
    setWebViewPath('');
  };

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonButtons slot="start">
            <IonBackButton />
          </IonButtons>
          <IonTitle>Edit Project</IonTitle>
          <IonButtons slot="end">
            <IonButton onClick={handleUpdate}>Update</IonButton>
          </IonButtons>
        </IonToolbar>
      </IonHeader>
      <IonContent>
        <IonLabel><b>Title</b></IonLabel>
        <IonInput value={title} onIonChange={e => setTitle(e.detail.value || '')} />
        <br />
        <IonLabel><b>Description</b></IonLabel>
        <IonInput value={description} onIonChange={e => setDescription(e.detail.value || '')} />
        <br />
        <IonLabel><b>Date</b></IonLabel>
        <IonDatetime
          presentation="date"
          value={date.toISOString()}
          onIonChange={e => {
            const value = e.detail.value;
            if (typeof value === 'string') {
              setDate(new Date(value));
            } else {
              log("Invalid date value:", value);
            }
          }}
        />
        <br />
        <IonLabel><b>Participants</b></IonLabel>
        <IonInput
          type="number"
          value={participants}
          onIonChange={e => setParticipants(Number.parseInt(e.detail.value || '0'))}
        />
        <br />
        <IonLabel><b>Status</b></IonLabel>
        <IonCheckbox checked={status} onIonChange={e => setStatus(e.detail.checked)} />
        <br />

        <IonButton expand="block" onClick={() => setShowMapModal(true)}>
          <IonIcon slot="start" icon={map} />
          Open Map
        </IonButton>

        {webViewPath && (
          <div style={{ textAlign: 'center' }}>
            <IonImg style={{ width: '60%', marginBottom: '10px' }} src={webViewPath} />
            <IonButton color="danger" onClick={handleDeletePhoto}>
              <IonIcon slot="start" icon={trash} />
              Delete Photo
            </IonButton>
          </div>
        )}
        {!webViewPath && (
          <IonFab vertical="bottom" horizontal="center" slot="fixed">
            <IonFabButton onClick={handlePhotoChange}>
              <IonIcon icon={camera} />
            </IonFabButton>
          </IonFab>
        )}

<IonModal
  isOpen={showMapModal}
  enterAnimation={enterAnimation}
  leaveAnimation={leaveAnimation}
  onDidDismiss={() => setShowMapModal(false)}
>
  <IonHeader>
    <IonToolbar>
      <IonTitle>Select Location</IonTitle>
      <IonButtons slot="end">
        <IonButton onClick={() => setShowMapModal(false)}>Close</IonButton>
      </IonButtons>
    </IonToolbar>
  </IonHeader>
  <IonContent>
    <MyMap
      lat={currentLatitude ?? 0} // Dacă nu există coordonate, folosește 0
      lng={currentLongitude ?? 0}
      onCoordsChanged={(lat, lng) => {
        setCurrentLatitude(lat);
        setCurrentLongitude(lng);
      }}
    />
  </IonContent>
</IonModal>


        <IonLoading isOpen={updating} />
        {updateError && (
          <div className={styles.errorMessage}>{updateError.message || 'Failed to update project'}</div>
        )}
      </IonContent>
    </IonPage>
  );
};
