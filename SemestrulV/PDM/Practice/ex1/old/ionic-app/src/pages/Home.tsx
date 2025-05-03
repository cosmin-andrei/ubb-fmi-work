import { IonContent, IonHeader, IonPage, IonTitle, IonToolbar } from '@ionic/react';
import MessagesList from '../components/MessageList';
import './Home.css';

const Home: React.FC = () => {
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Messages</IonTitle>
                </IonToolbar>
            </IonHeader>
            <IonContent fullscreen>
                <MessagesList />
            </IonContent>
        </IonPage>
    );
};

export default Home;
