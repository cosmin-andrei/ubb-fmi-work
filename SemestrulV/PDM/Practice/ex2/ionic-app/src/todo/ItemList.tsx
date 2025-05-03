import React, { useContext, useState } from 'react';
import { IonList, IonContent, IonLabel, IonButton } from '@ionic/react';
import { ItemContext } from './ItemProvider';
import Item from './Item';

const ItemList: React.FC = () => {
    const { questions, downloadProgress, fetchingError, fetchQuestions } = useContext(ItemContext);
    const [currentIndex, setCurrentIndex] = useState(0);
    const [answeredQuestions, setAnsweredQuestions] = useState(0);
    const [correctAnswers, setCorrectAnswers] = useState(0);
    const [selectedOption, setSelectedOption] = useState<number | null>(null);

    const currentQuestion = questions ? questions[currentIndex] : null;

    const handleAnswer = (index: number) => {
        setSelectedOption(index);
    };

    const handleNextQuestion = () => {
        if (selectedOption === null) return;

        setAnsweredQuestions(prev => prev + 1);
        if (selectedOption === currentQuestion?.indexCorrectOption) {
            setCorrectAnswers(prev => prev + 1);
        }

        if (currentIndex < (questions?.length ?? 0) - 1) {
            setCurrentIndex(prev => prev + 1);
            setSelectedOption(null);
        }
    };

    return (
        <IonContent>
            {/* ✅ Afișăm progresul descărcării */}
            {downloadProgress && <IonLabel>{downloadProgress}</IonLabel>}

            {fetchingError && (
                <>
                    <IonLabel color="danger">Failed to load questions. Please try again.</IonLabel>
                    <IonButton onClick={fetchQuestions}>Retry</IonButton>
                </>
            )}

            {questions && questions.length > 0 && currentQuestion ? (
                <>
                    <IonLabel>
                        <h2>Questions {answeredQuestions + 1}/{questions.length}</h2>
                        <h3>Correct answers: {correctAnswers}/{answeredQuestions}</h3>
                    </IonLabel>
                    <Item key={currentQuestion.id} item={currentQuestion} selectedOption={selectedOption} onAnswer={handleAnswer} />
                    <IonButton expand="full" onClick={handleNextQuestion} disabled={selectedOption === null}>
                        Next
                    </IonButton>
                </>
            ) : (
                <IonLabel>No questions available.</IonLabel>
            )}
        </IonContent>
    );
};

export default ItemList;
