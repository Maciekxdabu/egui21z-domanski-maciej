#ifndef MANAGEDPROJECTSDIALOG_H
#define MANAGEDPROJECTSDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QMessageBox>

#include "jsons.h"

namespace Ui {
class ManagedProjectsDialog;
}

class ManagedProjectsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManagedProjectsDialog(QWidget *parent = nullptr);
    ~ManagedProjectsDialog();

    void UpdateTable();

private slots:
    void OpenCreateNewDialog();
    void UpdateSelectedProject();
    void EditSubmittedReport();
    void CloseProject();

    void UpdateUI();

private:
    Ui::ManagedProjectsDialog *ui;

    QStandardItemModel *model;
    QStandardItemModel *reportsModel;

    QVector<Activities::Activity*> projects;
    QVector<Report*> tableReports;
    int timeSum;
};

#endif // MANAGEDPROJECTSDIALOG_H
