#include "jsons.h"

// ---------- Initialize static variables

QVector<Activities::Activity> ACTS = *(new QVector<Activities::Activity>());

QVector<Report*> REPS = *(new QVector<Report*>());
Report *Reports::currentReport = nullptr;

QString USER = "";
QDate DATE = *(new QDate());
QString DATAPATH = "data/";

// ---------- Activities class

Activities::Activities()
{
    fileName = ACTSFILENAME;
}

bool Activities::readJson()
{
    QFile loadFile(DATAPATH + fileName);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open activities file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonObject json = loadDoc.object();

    if (json.contains("activities") && json["activities"].isArray())
    {
        QJsonArray acts = json["activities"].toArray();

        activities.clear();
        activities.reserve(acts.size());
        for (int i=0; i<acts.size(); i++)
        {
            QJsonObject project = acts[i].toObject();

            Activity newAct;

            if (project.contains("code") && project["code"].isString())
                newAct.code = project["code"].toString();
            if (project.contains("manager") && project["manager"].isString())
                newAct.manager = project["manager"].toString();
            if (project.contains("name") && project["name"].isString())
                newAct.name = project["name"].toString();
            if (project.contains("budget") && project["budget"].isDouble())
                newAct.budget = project["budget"].toInt();
            if (project.contains("active") && project["active"].isBool())
                newAct.active = project["active"].toBool();
            if (project.contains("subactivities") && project["subactivities"].isArray())
            {
                QJsonArray subs = project["subactivities"].toArray();

                newAct.subactivities.clear();
                newAct.subactivities.reserve(subs.size());
                for (int j=0; j<subs.size(); j++)
                {
                    QJsonObject newSub = subs[j].toObject();

                    if (newSub.contains("code") && newSub["code"].isString())
                        newAct.subactivities.append(newSub["code"].toString());
                }
            }

            activities.append(newAct);
        }
    }

    return true;
}

bool Activities::writeJson() const
{
    //opening file
    QFile saveFile(DATAPATH + fileName);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open activities file.");
        return false;
    }

    QJsonObject jsonFile;//object that will be saved to file

    //building data to write
    QJsonArray actArray;

    //std::cout << "Number of projects: " << activities.length() << std::endl;
    for (const Activity &act : activities)
    {
        QJsonObject obj1;
        //std::cout << "Code of project: " << act.code.toStdString() << std::endl;
        obj1["code"] = act.code;
        obj1["manager"] = act.manager;
        obj1["name"] = act.name;
        obj1["budget"] = act.budget;
        obj1["active"] = act.active;

        QJsonArray arr1;
        for (const QString &str : act.subactivities)
        {
            QJsonObject obj2;
            obj2["code"] = str;
            arr1.append(obj2);
        }
        obj1["subactivities"] = arr1;

        actArray.append(obj1);
    }

    jsonFile["activities"] = actArray;

    //writing data
    saveFile.write(QJsonDocument(jsonFile).toJson());

    return true;
}

int Activities::GetActiveProjectIndex(int activeIndex)
{
    for (int i=0; i<activities.size(); i++)
    {
        if (activities[i].active)
        {
            if (activeIndex == 0)
            {
                return i;
            }
            activeIndex--;
        }
    }

    return -1;
}

Activities::Activity* Activities::GetActivity(QString aCode)
{
    for (int i=0; i<activities.size(); i++)
    {
        if (activities[i].code == aCode)
            return &activities[i];
    }

    return nullptr;
}

// ---------- Reports class

Report::Report(QString fName)//IMP: Must have .json file in attribute
{
    fileName = fName;

    QString tempFileName = fileName;
    tempFileName.remove(".json");

    QStringList strings = tempFileName.split("-", Qt::SkipEmptyParts);
    if (strings.size() != 3)
    {
        qWarning("Json file found in data folder is not a proper format for a report");
        return;
    }
    bool ok;
    int newYear = strings[1].toInt(&ok);
    if (!ok)
    {
        qWarning("Json file found in data folder is not a proper format for a report");
        return;
    }
    int newMonth = strings[2].toInt(&ok);
    if (!ok)
    {
        qWarning("Json file found in data folder is not a proper format for a report");
        return;
    }

    userName = strings[0];
    yearMonth.setDate(newYear, newMonth, 1);

    readJson();
}

Report::Report(QString uName, QDate month)
{
    userName = uName;
    yearMonth = month;
    fileName = uName + "-" + QString::number(month.year()) + "-" + QString::number(month.month()) + ".json";

    frozen = false;
    entries.clear();
    accepted.clear();
}

bool Report::IsCorrectReport(QString uName, QDate yMonth)
{
    if (uName == userName && yMonth.year() == yearMonth.year() && yMonth.month() == yearMonth.month())
        return true;
    else
        return false;
}

bool Report::HasTimeOnProject(QString projectCode)
{
    for (int i=0; i<entries.size(); i++)
    {
        if (entries[i].code == projectCode)
            return true;
    }

    return false;
}

bool Report::readJson()
{
    QFile loadFile(DATAPATH + fileName);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open activities file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonObject json = loadDoc.object();

    //TO DO - read json
    if (json.contains("frozen") && json["frozen"].isBool())
        frozen = json["frozen"].toBool();

    if (json.contains("entries") && json["entries"].isArray())
    {
        QJsonArray entriesArray = json["entries"].toArray();

        entries.clear();
        entries.reserve(entriesArray.size());
        for (int i=0; i<entriesArray.size(); i++)
        {
            QJsonObject json2 = entriesArray[i].toObject();

            Entry newEntry;

            if (json2.contains("date") && json2["date"].isString())
            {
                QStringList dateStrings = json2["date"].toString().split("-");
                newEntry.date = QDate(dateStrings[0].toInt(), dateStrings[1].toInt(), dateStrings[2].toInt());
            }
            if (json2.contains("code") && json2["code"].isString())
                newEntry.code = json2["code"].toString();
            if (json2.contains("subcode") && json2["subcode"].isString())
                newEntry.subcode = json2["subcode"].toString();
            if (json2.contains("time") && json2["time"].isDouble())
                newEntry.time = json2["time"].toInt();
            if (json2.contains("description") && json2["description"].isString())
                newEntry.description = json2["description"].toString();

            entries.append(newEntry);
        }
    }

    if (json.contains("accepted") && json["accepted"].isArray())
    {
        QJsonArray acceptArray = json["accepted"].toArray();

        accepted.clear();
        for (int i=0; i<acceptArray.size(); i++)
        {
            QJsonObject json3 = acceptArray[i].toObject();

            QString newKey;
            int newTime;

            if (json3.contains("code") && json3["code"].isString())
                newKey = json3["code"].toString();
            if (json3.contains("time") && json3["time"].isDouble())
                newTime = json3["time"].toInt();

            accepted.insert(newKey, newTime);
        }
    }

    return true;
}

bool Report::writeJson() const
{
    //opening file
    QFile saveFile(DATAPATH + fileName);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open report file.");
        return false;
    }

    QJsonObject jsonFile;//object that will be saved to file

    jsonFile["frozen"] = frozen;

    QJsonArray entriesArray;

    for (int i=0; i<entries.size(); i++)
    {
        QJsonObject newEntry;

        newEntry["date"] = QString::number(entries[i].date.year()) + "-" + QString::number(entries[i].date.month()) + "-" + QString::number(entries[i].date.day());
        newEntry["code"] = entries[i].code;
        newEntry["subcode"] = entries[i].subcode;
        newEntry["time"] = entries[i].time;
        newEntry["description"] = entries[i].description;

        entriesArray.append(newEntry);
    }

    jsonFile["entries"] = entriesArray;

    QJsonArray acceptArray;

    QList<QString> acceptKeys = accepted.keys();
    for (int i=0; i<accepted.size(); i++)
    {
        QJsonObject newAccept;

        //TO DO - accepted vector
        newAccept["code"] = acceptKeys[i];
        newAccept["time"] = accepted[acceptKeys[i]];

        acceptArray.append(newAccept);
    }

    jsonFile["accepted"] = acceptArray;

    //writing data
    saveFile.write(QJsonDocument(jsonFile).toJson());

    return true;
}

QString Report::GetUsername()
{
    return userName;
}

QDate Report::GetDate()
{
    return yearMonth;
}

// ---------- Reports class

Reports::Reports()
{

}

Report* Reports::GetReport(QString uName, QDate yMonth)
{
    for (int i=0; i<reports.size(); i++)
    {
        if (reports[i]->IsCorrectReport(uName, yMonth))
        {
            return reports[i];
        }
    }

    return nullptr;
}

QVector<Report*>* Reports::GetTimeSpent(QString projectCode)
{
    QVector<Report*> *reportList = new QVector<Report*>();
    reportList->clear();

    for (int i=0; i<reports.size(); i++)
    {
        if (reports[i]->HasTimeOnProject(projectCode))
            reportList->append(reports[i]);
    }

    return reportList;
}

void Reports::AddEntry(Report::Entry newEntry)
{
    ReloadCurrentReport(true);

    currentReport->entries.append(newEntry);
}

bool Reports::readJson()
{
    //TO DO - create using fileName Report constructor
    QString datapath = DATAPATH;
    datapath.remove(datapath.size() - 1, 1);
    QDir directory(datapath);
    if (directory.exists())
    {
        QStringList files = directory.entryList(QStringList() << "*.json");

        for (int i=0; i<files.size(); i++)
        {
            if (files[i] != ACTSFILENAME)
            {
                reports.append(new Report(files[i]));
            }
        }
    }

    return true;
}

bool Reports::writeJson()
{
    for (int i=0; i<reports.size(); i++)
    {
        reports[i]->writeJson();
    }

    return true;
}

void Reports::ReloadCurrentReport(bool createIfNone)
{
    if (currentReport == nullptr || !currentReport->IsCorrectReport(USER, DATE))//checks if correct currentReport linked
    {
        currentReport = GetReport(USER, DATE);
        if (createIfNone && currentReport == nullptr)//creates new currentReport if there is no one with specified USER and DATE
        {
            currentReport = new Report(USER, DATE);
            reports.append(currentReport);
        }
    }
}
