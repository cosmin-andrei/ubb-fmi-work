import React, { useState } from 'react';
import { IonItem, IonLabel, IonList } from '@ionic/react';
import { ItemProps } from './ItemProps';

interface ItemComponentProps {
    item: ItemProps;
    selectedOption: number | null;
    onAnswer: (index: number) => void;
}

export const Item: React.FC<ItemComponentProps> = ({ item, selectedOption, onAnswer }) => {
    const [answered, setAnswered] = useState(false);

    const handleSelect = (index: number) => {
        if (answered) return;
        onAnswer(index);
        setAnswered(true);
    };

    return (
        <IonList>
            <IonLabel>
                <h1>{item.text}</h1>
            </IonLabel>
            {item.options.map((option, index) => (
                <IonItem
                    key={index}
                    button={!answered}
                    onClick={() => handleSelect(index)}
                    color={selectedOption !== null ?
                        (index === item.indexCorrectOption ? 'success' : 'danger')
                        : undefined}
                >
                    <IonLabel>{option}</IonLabel>
                </IonItem>
            ))}
        </IonList>
    );
};

export default Item;
