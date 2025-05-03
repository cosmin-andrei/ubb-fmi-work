import React, { useState, useEffect } from "react";
import { IonPage, IonHeader, IonToolbar, IonTitle, IonContent, IonInput, IonButton, IonToast, IonProgressBar } from "@ionic/react";
import axios from "axios";
import { useHistory } from "react-router-dom";

const Auth: React.FC = () => {
    const [participantId, setParticipantId] = useState("");
    const [error, setError] = useState("");
    const [loading, setLoading] = useState(false);
    const [progress, setProgress] = useState(0);
    const [questionsDownloaded, setQuestionsDownloaded] = useState(0);
    const [totalQuestions, setTotalQuestions] = useState(0);
    const history = useHistory();

    useEffect(() => {
        if (localStorage.getItem("questions")) {
            history.push("/home");
        }
    }, [history]);

    const fetchQuestions = async (questionIds: number[]) => {
        setTotalQuestions(questionIds.length);
        const downloadedQuestions: any[] = [];

        for (let i = 0; i < questionIds.length; i++) {
            try {
                const response = await axios.get(`http://localhost:3000/question/${questionIds[i]}`);
                downloadedQuestions.push(response.data);
                setQuestionsDownloaded(i + 1);
                setProgress((i + 1) / questionIds.length);
            } catch (error) {
                setError("Failed to download questions. Try again.");
                return;
            }
        }

        localStorage.setItem("questions", JSON.stringify(downloadedQuestions));
        history.push("/home");
    };

    const handleLogin = async () => {
        if (!participantId) {
            setError("Please enter your ID");
            return;
        }

        setLoading(true);
        setProgress(0);
        setQuestionsDownloaded(0);

        try {
            const response = await axios.post("http://localhost:3000/auth", { id: participantId });
            const { token, questionIds } = response.data;

            localStorage.setItem("token", token);
            localStorage.setItem("participantId", participantId);

            await fetchQuestions(questionIds);
        } catch (err) {
            setError("Invalid ID or server error");
            setLoading(false);
        }
    };

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Quiz Login</IonTitle>
                </IonToolbar>
            </IonHeader>
            <IonContent className="ion-padding">
                {!loading ? (
                    <>
                        <IonInput placeholder="Enter your ID" onIonChange={(e) => setParticipantId(e.detail.value!)} />
                        <IonButton expand="full" onClick={handleLogin}>Submit</IonButton>
                    </>
                ) : (
                    <>
                        <IonProgressBar value={progress}></IonProgressBar>
                        <p>Downloading {questionsDownloaded}/{totalQuestions}</p>
                    </>
                )}
                {error && <IonButton expand="full" color="danger" onClick={handleLogin}>Retry</IonButton>}
                <IonToast isOpen={!!error} message={error} duration={2000} onDidDismiss={() => setError("")} />
            </IonContent>
        </IonPage>
    );
};

export default Auth;
