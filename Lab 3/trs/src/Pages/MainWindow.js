import React, { useState, useEffect } from "react";
import axios from "axios";

function MainWindow(props) {
    const [entryList, setEntryList] = useState({ entries: [] });

    useEffect(() => {
        const fetchData = async () => {
            const config = {
                method: 'get',
                url: '/api/getReport',
                params:{
                    username: props.uName,
                    date: props.uDate
                }
            }
            const result = await axios(config);

            console.log(result.data);
            setEntryList(result.data)
        };
        fetchData();
    }, []);

    return (
        <div>
            <h2>
                MainWindow Page
            </h2>
            <table>
                <tr>
                    <th>
                        Project Code
                    </th>
                    <th>
                        Time Spent
                    </th>
                    <th>
                        Description
                    </th>
                </tr>
                {entryList.entries.map(item => (
                <tr>
                    <td>
                        {item.code}
                    </td>
                    <td>
                        {item.time}
                    </td>
                    <td>
                        {item.description}
                    </td>
                </tr>
                ))}
            </table>
        </div>
    );
};

export default MainWindow;