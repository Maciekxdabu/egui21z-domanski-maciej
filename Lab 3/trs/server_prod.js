const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();

app.use(express.static(path.join(__dirname, 'build')))

app.get('/api/projList', (req, res) => {
    fileName = 'jsons/activity.json';
    fs.readFile(fileName, (err, out2) => {
        if (err) throw err;
        content = JSON.parse(out2);
        res.json(content);
    });
})
app.get('/api/getReport', (req, res) => {
    _username = req.query["username"];
    _date = req.query["date"];
    ReadReport(_username, _date, res);
})
//app.get('/api/projList', (req, res) => res.json(data))
app.listen(5000)


function ReadReport(username, date, res) {
    var cutDate = date.slice(0, 7);
    var filename = username + '-' + cutDate + '.json';
    //var content = ReadFile(path.join(__dirname, 'jsons', filename));
    fs.readFile(path.join(__dirname, 'jsons', filename), (err, out2) => {
        if (err) throw err;
        content = JSON.parse(out2);

        var obj = {};
        obj.entries = new Array();
        var index = 0;
        for (var i = 0; i<content.entries.length; i++) {
            if (content.entries[i].date != date)
            {
                continue;
            }

            var newObj = {}
            newObj.code = content.entries[i].code;
            newObj.time = content.entries[i].time;
            newObj.description = content.entries[i].description;
            newObj.date = content.entries[i].date;
            obj.entries[index] = newObj;
            index++;
        }
        res.send(obj);
    });
}

function AddEntry(username, date, newEntry) {
    //TO DO
}

function EditEntry(username, date, newEntry) {
    //TO DO
}

function DeleteEntry(username, date, newEntry) {
    //TO DO
}

function ReadFile(address, res) {
    fs.readFile(address, (err, out2) => {
        if (err) throw err;
        content = JSON.parse(out2);
        res.json(content);
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
    let data = JSON.stringify(content)
    fs.writeFile(name, data, function (err, result) {
        if (err) console.log('Error:', err)
    })
}

/*const data =
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
}*/