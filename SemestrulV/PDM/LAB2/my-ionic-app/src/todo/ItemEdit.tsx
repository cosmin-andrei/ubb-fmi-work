import React, { useCallback, useContext, useEffect, useState } from 'react';
import {
  IonButton,
  IonButtons,
  IonContent,
  IonHeader,
  IonInput,
  IonLoading,
  IonPage,
  IonTitle,
  IonToolbar,
  IonCheckbox
} from '@ionic/react';
import { getLogger } from '../core';
import { ItemContext } from './ItemProvider';
import { RouteComponentProps } from 'react-router';
import { ItemProps } from './ItemProps';

const log = getLogger('ItemEdit');

interface ItemEditProps extends RouteComponentProps<{
  id?: string;
}> { }

const ItemEdit: React.FC<ItemEditProps> = ({ history, match }) => {
  const { items, saving, savingError, saveItem } = useContext(ItemContext);
  const [name, setName] = useState('');
  const [description, setDescription] = useState('');
  const [date, setDate] = useState(new Date());
  const [participants, setParticipants] = useState(0);
  const [status, setStatus] = useState(false);
  const [item, setItem] = useState<ItemProps>();

  useEffect(() => {
    log('useEffect');

    const routeId = match.params.id || '';
    const foundItem = items?.find(it => it.id === routeId);

    setItem(foundItem);
    if (foundItem) {
      setName(foundItem.name);
      setDescription(foundItem.description);
      setDate(new Date(foundItem.date)); // Ensure this is a valid date
      setParticipants(foundItem.participants);
      setStatus(foundItem.status);
      // alert(foundItem.status);
    }
  }, [match.params.id, items]);

  const handleSave = useCallback(() => {
    const editedItem = item
      ? { ...item, name, description, date, participants, status }
      : { name, description, date, participants, status };

    log(status);

    saveItem && saveItem(editedItem)
      .then(() => history.goBack())
      .catch(error => {
        console.error("Error saving item: ", error);
        alert("Error saving item: " + error.message); // Show alert on error
      });
  }, [item, saveItem, name, description, date, participants, status, history]);

  const handleCancel = useCallback(() => {
    history.goBack();
  }, [history]);

  useEffect(() => {
    if (savingError) {
      alert(savingError.message || 'Failed to save item'); // Show alert on saving error
    }
  }, [savingError]);

  log('render');
  return (
    <IonPage>
      <IonHeader>
        <IonToolbar>
          <IonTitle>Edit</IonTitle>
          <IonButtons slot="end">
            <IonButton onClick={handleSave}>
              Save
            </IonButton>
          </IonButtons>
        </IonToolbar>
      </IonHeader>
      <IonContent>
        <IonInput
          value={name}
          onIonChange={e => setName(e.detail.value || '')}
          placeholder='Name'
        />

        <IonInput
          value={description}
          onIonChange={e => setDescription(e.detail.value || '')}
          placeholder='Description'
        />

        <IonInput
          type="date"
          value={date.toISOString().split('T')[0]}
          onIonChange={e => {
            const selectedDate = new Date(e.detail.value!);
            setDate(selectedDate);
          }}
          placeholder='Select Date'
        />

        <IonInput
          type="number"
          value={participants !== 0 ? participants.toString() : ''}
          onIonChange={e => {
            const value = e.detail.value;
            setParticipants(value ? parseInt(value, 10) : 0);
          }}
          placeholder='No. participants'
        />

        <IonCheckbox
          checked={status}
          onIonChange={e => {
            const checkedValue = e.detail.checked;
            setStatus(checkedValue);
          }}
        />
        <label>&nbsp;Not status</label>


        <IonLoading isOpen={saving} />
      </IonContent>
    </IonPage>
  );
};

export default ItemEdit;
