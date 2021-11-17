#include "managedprojectsdialog.h"
#include "ui_managedprojectsdialog.h"
#include "newprojectdialog.h"

ManagedProjectsDialog::ManagedProjectsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagedProjectsDialog)
{
    ui->setupUi(this);

    //buttons
    connect(ui->createNewButton, &QPushButton::clicked, this, &ManagedProjectsDialog::OpenCreateNewDialog);

    model = new QStandardItemModel();

    UpdateTable();
}

ManagedProjectsDialog::~ManagedProjectsDialog()
{
    delete ui;

    delete model;
}

void ManagedProjectsDialog::OpenCreateNewDialog()
{
    NewProjectDialog *newProjectDialog = new NewProjectDialog();
    DialogCode exitCode = (DialogCode)newProjectDialog->exec();

    if (exitCode == DialogCode::Accepted)
    {
        Activities::Activity newAct;
        newAct.active = true;
        newProjectDialog->GetProjectData(newAct);
        ACTS.append(newAct);

        UpdateTable();
    }

    delete newProjectDialog;
}

void ManagedProjectsDialog::UpdateTable()
{
    model->clear();

    for (int i=0; i<ACTS.size(); i++)
    {
        QString tooltip = ACTS[i].name + " (" + ACTS[i].code + ")\nactive: " + (ACTS[i].active ? "yes\nbudget: " : "no\nbudget: ") + QString::number(ACTS[i].budget);
        QStandardItem *item = new QStandardItem(ACTS[i].code);
        item->setToolTip(tooltip);
        model->setItem(i, 0, item);
        QStandardItem *item2 = new QStandardItem(ACTS[i].name);
        item2->setToolTip(tooltip);
        model->setItem(i, 1, item2);
    }

    model->setHeaderData(0, Qt::Horizontal, "Code");
    model->setHeaderData(1, Qt::Horizontal, "Name");

    ui->projectsTable->setModel(model);
}
