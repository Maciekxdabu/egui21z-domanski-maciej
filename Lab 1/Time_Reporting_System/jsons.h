#ifndef JSONS_H
#define JSONS_H

#include <QJsonObject>
#include <QJsonArray>

#include <QString>
#include <QVector>
#include <QDate>

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

    void readJson(const QJsonObject &json);
    void writeJson(QJsonObject &json) const;

        //variables
    QVector<Activity> activities;
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

    Report();

    void readJson(const QJsonObject &json);
    void writeJson(QJsonObject &json) const;

        //variables
    bool frozen;
    QVector<Entry> entries;
    QMap<QString, int> accepted;
};

#endif // JSONS_H
