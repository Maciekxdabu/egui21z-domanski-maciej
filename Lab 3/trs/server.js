const express = require('express');
const fs = require('fs');
const app = express();
const data =
{
    "activities":
    [
        {
            "code":"Dev-1",
            "manager":"jan",
            "name":"Development",
            "budget":200
        },
        {
            "code":"DT-2",
            "manager":"kowal",
            "name":"Data Mining",
            "budget":300
        }
    ]
}
app.get('/api/projList', (req, res) => {
    fileName = 'jsons/activity.json';
    ReadFile(fileName, res);
})
//app.get('/api/projList', (req, res) => res.json(data))
app.listen(5000)



function ReadFile(path, res) { // read file from given path and send the contents in res
    fs.readFile(path, (err, out2) => {
        if (err) throw err; // if error, throw the error
        content = JSON.parse(out2); // otherwise parse the binary output into JSON
        //console.log(content);
        res.json(content); // send json response ('content' needs to be in json format for this to work)
    });
}

function WriteFile(name) {
    let content = 
    {
        "activities":
        [
            {
                "code":"Dev-1",
                "manager":"jan",
                "name":"Development",
                "budget":200
            },
            {
                "code":"DT-2",
                "manager":"kowal",
                "name":"Data Mining",
                "budget":300
            }
        ]
    }
    let data = JSON.stringify(content) // change the data structure into a JSON string
    fs.writeFile(name, data, function (err, result) {
        if (err) console.log('Error:', err) // if error : log it
    })
}