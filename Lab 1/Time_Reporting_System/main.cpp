﻿#include "mainwindow.h"
#include "jsons.h"

#include <QApplication>
#include <QInputDialog>
#include <QDir>

//static variables declared in json.h for global access (in all Dialogs)
Activities actObject;

//functions declarations
bool LoadConfig();

// ---------- main function

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    LoadData();

    bool acceptedInput = false;
    while (!acceptedInput || USER.isEmpty())
    {
        USER = QInputDialog::getText(w.menuWidget(), "Enter username",
                                     "User name:", QLineEdit::Normal,
                                     "", &acceptedInput);
    }
    w.PublicUpdateData();

    int returnCode = a.exec();

    SaveData();

    return returnCode;
}

// ---------- Functions (declarations above main)

bool SaveData()
{
    actObject.writeJson();

    Reports::writeJson();

    return true;
}

bool LoadData()
{
    actObject.readJson();

    Reports::readJson();

    return true;
}
