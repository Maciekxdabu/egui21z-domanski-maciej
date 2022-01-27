import React, { useState, useEffect } from "react";
import axios from "axios";
import { Link } from "react-router-dom";

function MainWindow(props) {
    const [entryList, setEntryList] = useState({ entries: [] });
    const [timeSum, setTimeSum] = useState(0);

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

            var sum = 0;
            for (var i = 0; i<result.data.entries.length; i++)
            {
                sum += result.data.entries[i].time;
            }
            setTimeSum(sum);

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
                    <th></th>
                    <th></th>
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
                    <td>
                        <Link to='/entrydialog'>
                            <button type="button">
                                Edit
                            </button>
                        </Link>
                        <button type="button">
                            Delete
                        </button>
                    </td>
                </tr>
                ))}
            </table>
            <h4>
                Time spent on activities today: {timeSum}
            </h4>
        </div>
    );
};

export default MainWindow;