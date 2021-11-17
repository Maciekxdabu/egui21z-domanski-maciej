#ifndef MANAGEDPROJECTSDIALOG_H
#define MANAGEDPROJECTSDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

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

private:
    Ui::ManagedProjectsDialog *ui;

    QStandardItemModel *model;
};

#endif // MANAGEDPROJECTSDIALOG_H
