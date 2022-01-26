import { Link, Route, Routes } from "react-router-dom";
import './App.css';
import MainWindow from "./Pages/MainWindow";
import EntryDialog from "./Pages/EntryDialog";

function App() {
  return (
    <div>
      DEBUG START
      <nav>
        <ul>
          <li> <Link to='/'>Home</Link> </li>
          <li> <Link to='/mainwindow'>Main Window</Link> </li>
          <li> <Link to='/entrydialog'>Entry Dialog</Link> </li>
        </ul>
      </nav>
      DEBUG END
      <Routes>
        <Route path='/' element={<h1>NO PAGE</h1>} />
        <Route path='/mainwindow' element={<MainWindow/>} />
        <Route path='/entrydialog' element={<EntryDialog/>} />
      </Routes>
    </div>
  );
}

export default App;



/*import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}

export default App;*/
