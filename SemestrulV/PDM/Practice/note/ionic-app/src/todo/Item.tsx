import React from 'react';
import { IonItem, IonLabel, IonButton } from '@ionic/react';
import { ItemProps } from './ItemProps';

interface ItemComponentProps {
    item: ItemProps;
    onDelete: () => void;
}

const Item: React.FC<ItemComponentProps> = ({ item, onDelete }) => {
    const isDeleted = item.deleted;

    return (
        <IonItem>
            <IonLabel className={isDeleted ? 'text-gray-500' : ''}>
                <h2>{item.text}</h2>
                <p>{new Date(item.date).toLocaleString()}</p>
            </IonLabel>
            <IonButton
                slot="end"
                color="danger"
                onClick={onDelete}
                disabled={isDeleted}
            >
                Șterge
            </IonButton>
        </IonItem>
    );
};

export default Item;