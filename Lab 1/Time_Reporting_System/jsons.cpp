#include "jsons.h"

// ---------- Activities class

Activities::Activities()
{

}

void Activities::readJson(const QJsonObject &json)
{

}

void Activities::writeJson(QJsonObject &json) const
{
    QJsonArray actArray;

    for (const Activity &act : activities)
    {
        QJsonObject obj1;
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

    json["activities"] = actArray;
}

// ---------- Reports class

Report::Report()
{

}

void Report::readJson(const QJsonObject &json)
{

}

void Report::writeJson(QJsonObject &json) const
{

}
