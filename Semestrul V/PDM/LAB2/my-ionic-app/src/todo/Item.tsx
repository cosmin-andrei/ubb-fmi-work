import React, { memo } from 'react';
import { IonItem, IonLabel, IonDatetime, IonCheckbox } from '@ionic/react';
import { getLogger } from '../core';
import { ItemProps } from './ItemProps';

const log = getLogger('Item');

interface ItemPropsExt extends ItemProps {
  onEdit: (id?: string) => void;
}

const Item: React.FC<ItemPropsExt> = ({ id, name, description, date, participants, status, onEdit }) => {
  return (
    <IonItem onClick={() => onEdit(id)}>
      <IonLabel>{name}</IonLabel>
      <IonLabel>{description}</IonLabel>
        {/* <IonDatetime value={date}></IonDatetime> */}
        <IonLabel>{participants}</IonLabel>
        <IonCheckbox checked={!status}></IonCheckbox>
    </IonItem>
  );
};

export default memo(Item);
