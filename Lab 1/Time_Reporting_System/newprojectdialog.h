#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QInputDialog>
#include <QStandardItemModel>

#include "jsons.h"

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = nullptr);
    ~NewProjectDialog();

    void GetProjectData(Activities::Activity &newAct);

    void AddSubactivity();
    void DeleteSubactivity();

    void CheckProjectsCode(QString newCode);

private:
    Ui::NewProjectDialog *ui;

    QStandardItemModel *subcategoriesModel;
};

#endif // NEWPROJECTDIALOG_H
