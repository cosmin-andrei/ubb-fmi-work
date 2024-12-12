import { Redirect, Route } from 'react-router-dom';
import { IonApp, IonRouterOutlet, setupIonicReact } from '@ionic/react';
import { IonReactRouter } from '@ionic/react-router';
import Home from './pages/Home';

/* Core CSS required for Ionic components to work properly */
import '@ionic/react/css/core.css';

/* Basic CSS for apps built with Ionic */
import '@ionic/react/css/normalize.css';
import '@ionic/react/css/structure.css';
import '@ionic/react/css/typography.css';

/* Optional CSS utils that can be commented out */
import '@ionic/react/css/padding.css';
import '@ionic/react/css/float-elements.css';
import '@ionic/react/css/text-alignment.css';
import '@ionic/react/css/text-transformation.css';
import '@ionic/react/css/flex-utils.css';
import '@ionic/react/css/display.css';

/* Theme variables */
import './theme/variables.css';

import { ProjectsList } from './projects/ProjectList';
import { ProjectProvider } from './projects/ProjectProvider';
import { ProjectEdit } from './projects/ProjectEdit';
import { ProjectAdd } from './projects/ProjectAdd';
import { AuthProvider, Login, PrivateRoute } from './auth';

setupIonicReact();

const App: React.FC = () => (
  <IonApp>
      <IonReactRouter>
        <IonRouterOutlet>
          <AuthProvider>
            <Route path="/login" component={Login} exact={true}/>
            <ProjectProvider>
              <PrivateRoute path="/projects" component={ProjectsList} exact={true} />
              <Route path="/project" component={ProjectAdd} exact={true}/>
              <Route path="/project/:id" component={ProjectEdit} exact={true}/>
            </ProjectProvider>
            <Route exact path="/" render={() => <Redirect to="/projects"/>}/>
          </AuthProvider>
        </IonRouterOutlet>
      </IonReactRouter>
  </IonApp>
);

export default App;
