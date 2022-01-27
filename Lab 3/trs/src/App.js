import { Link, Route, Routes } from "react-router-dom";
import './App.css';
import MainWindow from "./Pages/MainWindow";
import EntryDialog from "./Pages/EntryDialog";
import { useState } from 'react';

function App() {
  const [username, setUsername] = useState('jan')
  const [date, setDate] = useState('2022-01-26')

  function handleNewUserName(evt) {
    setUsername(evt.target.value)
  }

  function handleNewDate(evt) {
    setDate(evt.target.value)
  }

  function handleEntryReturn(entry) {
    //TO DO - add/edit entry
    console.log(entry);
  }

  return (
    <div>
      <Routes>
        <Route path='/' element={
          <div>
            <div>
              <input type="date" value={date} onChange={handleNewDate} />
            </div>
            <div>
              Username: {username}
            </div>
            <MainWindow uName={username} uDate={date} />
            <Link to='/entrydialog'>
              <button type="button">
                Add Entry
              </button>
            </Link>
          </div>
        } />
        <Route path='/entrydialog' element={
        <EntryDialog onEntry={handleEntryReturn} />
        } />
      </Routes>
    </div>
  );
}

export default App;
