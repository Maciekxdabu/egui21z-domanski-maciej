#include "mainwindow.h"
#include "jsons.h"

#include <QApplication>
#include <QFile>

#include <QJsonDocument>

Activities activities;
QVector<Report> reports;

bool SaveData();
bool LoadData();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //activities save test
    Activities::Activity newAct;
    newAct.code = "Test code";
    newAct.subactivities.append("CODE-1");
    newAct.subactivities.append("CODE-X");
    activities.activities.append(newAct);
    SaveData();

    return a.exec();
}

bool SaveData()
{
    QFile saveFile(QStringLiteral("data/activity.json"));//TO DO - delete data folder (or make sure program creates it when not presented)

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open activities file.");
        return false;
    }

    QJsonObject actObject;
    activities.writeJson(actObject);
    saveFile.write(QJsonDocument(actObject).toJson());

    return true;
}

bool LoadData()
{

}
