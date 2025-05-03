import React, { useEffect, useState } from 'react';
import { IonItem, IonLabel } from '@ionic/react';
import { ItemProps } from './ItemProps';

interface ItemComponentProps {
    item: ItemProps;
    onRead: (id: number) => void;
}

export const Item: React.FC<ItemComponentProps> = ({ item, onRead }) => {
    const [highlight, setHighlight] = useState(!item.read);

    useEffect(() => {
        if (!item.read) {
            setTimeout(() => setHighlight(false), 1000);
            if (item.id !== undefined) {
                onRead(item.id);
            }

        }
    }, [item, onRead]);

    return (
        <IonItem lines="full">
            <IonLabel style={{ fontWeight: highlight ? 'bold' : 'normal' }}>
            <p>{item.text}</p>
                <p style={{ fontSize: '0.8em', color: 'gray' }}>
                    {new Date(item.created).toLocaleString()}
                </p>
            </IonLabel>
        </IonItem>

    );
};

export default Item;
