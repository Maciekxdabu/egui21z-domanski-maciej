#include "mainwindow.h"
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

    if (!LoadConfig())//TO DO - implement config
    {
        //TO DO - ask user for datapath
    }

    LoadData();

    bool acceptedInput = false;
    while (!acceptedInput || USER.isEmpty())
    {
        USER = QInputDialog::getText(w.menuWidget(), "Enter username",
                                     "User name:", QLineEdit::Normal,
                                     QDir::home().dirName(), &acceptedInput);
    }
    w.PublicUpdateData();

    int returnCode = a.exec();

    SaveData();

    return returnCode;
}

// ---------- Functions (declarations above main)

bool LoadConfig()
{
    //TO DO
    //-loading config file
    //  -data folder path

    return true;
}

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
