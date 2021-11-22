#ifndef JSONS_H
#define JSONS_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QString>
#include <QVector>
#include <QDate>
#include <QFile>
#include <QDir>

#define ACTS Activities::activities
#define ACTSFILENAME "activity.json"

#define USER PublicData::username
#define DATE PublicData::currentDate
#define DATAPATH PublicData::dataFolderPath

#define REPS Reports::reports
//Always make sure that is not nullptr by calling Reports::ReloadCurrentReport();
#define MAINREP Reports::currentReport

class Activities
{
public:
    struct Activity
    {
        QString code;
        QString manager;
        QString name;
        int budget;
        bool active;
        QVector<QString> subactivities;//saved with a key "code" and its value in json
    };

    Activities();

    bool readJson();
    bool writeJson() const;

    static int GetActiveProjectIndex(int activeIndex);//returns an active project of the given number
    static Activity* GetActivity(QString aCode);

        //variables
    static QVector<Activity> activities;

private:
    QString fileName;
};

class Report
{
public:
    struct Entry
    {
        QDate date;
        QString code;
        QString subcode;
        int time;
        QString description;
    };

    Report(QString fName);//used when loading report from file
    Report(QString uName, QDate month);//used when creating new report

    bool IsCorrectReport(QString uName, QDate yMonth);
    bool HasTimeOnProject(QString projectCode);

    bool readJson();
    bool writeJson() const;

    QString GetUsername();
    QDate GetDate();

        //variables
    bool frozen;
    QVector<Entry> entries;
    QMap<QString, int> accepted;//map is: <Project code, time>

private:
    QString userName;
    QString fileName;
    QDate yearMonth;
};

class Reports
{
public:
    Reports();

    static Report* GetReport(QString uName, QDate yMonth);//used for user on current month
    static QVector<Report*>* GetTimeSpent(QString projectCode);//used for managers to calculate time spent on their project

    static void AddEntry(Report::Entry newEntry);//adds new Entry for current user and date (report)

    static bool readJson();
    static bool writeJson();

    static void ReloadCurrentReport(bool createIfNone);

    //variables
    static QVector<Report*> reports;
    static Report *currentReport;
};

class PublicData
{
public:

    static QString username;
    static QDate currentDate;
    static QString dataFolderPath;
};

//functions declaration
bool SaveData();
bool LoadData();

#endif // JSONS_H
