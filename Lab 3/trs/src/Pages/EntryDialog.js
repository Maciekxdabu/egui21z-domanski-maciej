import axios from "axios";
import React, { useEffect, useState } from "react";
import { Link } from "react-router-dom";

function EntryDialog(props) {
    // ---------- Hooks
    const [project, setProject] = useState('')
    const [time, setTime] = useState('1')
    const [description, setDescription] = useState('')

    const [projectsMap, setProMap] = useState({});
    useEffect(() => {
        const fetchData = async () => {
            const config = {
                method: 'get',
                url: '/api/projList'
            }
            const result = await axios(config);

            var map1 = {};
            for (var i = 0; i < result.data.activities.length; i++)
            {
                map1[result.data.activities[i].code] = result.data.activities[i].name;
                if (i == 0)
                {
                    setProject(result.data.activities[i].code);
                }
            }
            setProMap(map1);
        };
        fetchData();
    }, []);

    function handleProject(event) {
        setProject(event.target.value)
    }
    function handleTime(event) {
        setTime(event.target.value)
    }
    function handleDescription(event) {
        setDescription(event.target.value)
    }

    // ---------- Functions
    function handleReturnEntry() {
        var entry = {
            project: project,
            time: time,
            description: description
        }
        props.onEntry(entry)
    }

    // ---------- Return
    return (
        <div>
            <h2>
                EntryDialog Page
            </h2>
            <div>
                Project:
                <select value={project} onChange={handleProject}>
                    {Object.entries(projectsMap).map(([key, value]) => <option value={key}>{value}</option>)}
                </select>
            </div>
            <div>
                Time Spent:
                <input type="number" min="1" value={time} onChange={handleTime} />
            </div>
            <div>
                Description:
                <textarea value={description} onChange={handleDescription} />
            </div>
            <input type="button" value="Submit" onClick={handleReturnEntry} />
            <Link to='/'>
                <button type="button">
                    Cancel
                </button>
            </Link>
        </div>
    );
};

export default EntryDialog;