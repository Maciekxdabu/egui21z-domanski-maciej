#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include "jsons.h"

#include <QDialog>

namespace Ui {
class EntryDialog;
}

class EntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryDialog(QWidget *parent = nullptr);
    ~EntryDialog();

    void LoadEntry(Report::Entry &newEntry);//loads Entry from Dialog
    void PushEntry(Report::Entry &pushEntry);//loads Entry to Dialog

private:
    Ui::EntryDialog *ui;

    void Initialize();
    void RefreshSubcategories();
};

#endif // ENTRYDIALOG_H
