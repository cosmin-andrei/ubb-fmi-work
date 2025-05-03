import React, { useEffect, useState } from "react";
import {
    IonPage,
    IonHeader,
    IonToolbar,
    IonTitle,
    IonContent,
    IonButton,
    IonRadio,
    IonRadioGroup,
    IonItem,
    IonLabel,
    IonList
} from "@ionic/react";
import axios from "axios";
import { useHistory } from "react-router-dom";

interface Question {
    id: number;
    text: string;
    options: string[];
    indexCorrectOption: number;
}

const Home: React.FC = () => {
    const [questions, setQuestions] = useState<Question[]>([]);
    const [currentIndex, setCurrentIndex] = useState(0);
    const [selectedAnswer, setSelectedAnswer] = useState<number | null>(null);
    const [answeredCount, setAnsweredCount] = useState(0);
    const [correctCount, setCorrectCount] = useState(0);
    const history = useHistory();

    useEffect(() => {
        const fetchQuestions = async () => {
            try {
                const response = await axios.post("http://localhost:3000/auth", {
                    id: localStorage.getItem("participantId"),
                });
                const { questionIds } = response.data;

                const fetchedQuestions = await Promise.all(
                    questionIds.map(async (id: number) => {
                        const res = await axios.get(`http://localhost:3000/question/${id}`);
                        return res.data;
                    })
                );

                setQuestions(fetchedQuestions);
                localStorage.setItem("questions", JSON.stringify(fetchedQuestions));
            } catch (error) {
                console.error("Error fetching questions:", error);
            }
        };

        const storedQuestions = localStorage.getItem("questions");
        if (storedQuestions) {
            setQuestions(JSON.parse(storedQuestions));
        } else {
            fetchQuestions();
        }

        // Fetch new questions every 15 seconds
        const interval = setInterval(fetchQuestions, 15000);
        return () => clearInterval(interval);
    }, []);

    useEffect(() => {
        if (questions.length > 0) {
            const timer = setTimeout(() => handleNextQuestion(), 5000);
            return () => clearTimeout(timer);
        }
    }, [currentIndex, selectedAnswer, questions]);

    const handleNextQuestion = () => {
        if (selectedAnswer !== null) {
            if (selectedAnswer === questions[currentIndex].indexCorrectOption) {
                setCorrectCount((prev) => prev + 1);
            }
            setAnsweredCount((prev) => prev + 1);
        }

        if (currentIndex + 1 < questions.length) {
            setCurrentIndex((prev) => prev + 1);
            setSelectedAnswer(null);
        } else {
            alert(`Quiz completed! Score: ${correctCount}/${questions.length}`);
            history.push("/auth"); // Redirect to login after quiz
        }
    };

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>
                        Question {answeredCount + 1}/{questions.length} | Correct: {correctCount}/{answeredCount}
                    </IonTitle>
                </IonToolbar>
            </IonHeader>
            <IonContent className="ion-padding">
                {questions.length > 0 && (
                    <>
                        <h3>{questions[currentIndex].text}</h3>
                        <IonRadioGroup
                            value={selectedAnswer}
                            onIonChange={(e) => setSelectedAnswer(e.detail.value)}
                        >
                            {questions[currentIndex].options.map((option, index) => (
                                <IonItem key={index}>
                                    <IonLabel>{option}</IonLabel>
                                    <IonRadio slot="start" value={index} />
                                </IonItem>
                            ))}
                        </IonRadioGroup>
                        <IonButton expand="full" onClick={handleNextQuestion}>Next</IonButton>
                    </>
                )}
            </IonContent>
        </IonPage>
    );
};

export default Home;
