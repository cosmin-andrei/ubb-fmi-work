import React from 'react'
import ReactDOM from 'react-dom/client'
import UserApp from './UserApp.jsx';
import './index.css'

ReactDOM.createRoot(document.getElementById('root')).render(
  //<React.StrictMode>
    <UserApp />
 // </React.StrictMode>,
)

/*



const container=document.getElementById('root');
const root=createRoot(container);
root.render( <UserApp/>);

ReactDOM.render(
  <div>
 <UserApp/>
  </div>,
  document.getElementById('root')
);*/
