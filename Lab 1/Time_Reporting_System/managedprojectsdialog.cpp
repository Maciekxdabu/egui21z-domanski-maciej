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

    //updates
    connect(ui->projectsTable, &QTableView::clicked, this, &ManagedProjectsDialog::UpdateSelectedProject);
    connect(ui->editTimeButton, &QPushButton::clicked, this, &ManagedProjectsDialog::EditSubmittedReport);
    connect(ui->closeProjectButton, &QPushButton::clicked, this, &ManagedProjectsDialog::CloseProject);

    model = new QStandardItemModel();
    reportsModel = new QStandardItemModel();

    ui->projectsTable->setModel(model);
    ui->reportsTable->setModel(reportsModel);

    UpdateTable();
}

ManagedProjectsDialog::~ManagedProjectsDialog()
{
    delete ui;

    delete model;
    delete reportsModel;
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
        if (ACTS[i].manager != USER)
            continue;

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

    UpdateUI();
}

void ManagedProjectsDialog::UpdateSelectedProject()
{
    int index = ui->projectsTable->currentIndex().row();

    if (index < 0)
    {
        return;
    }

    QString pCode = model->item(index, 0)->text();

    reportsModel->clear();

    int currentRow = 0;
    for (int i=0; i<REPS.size(); i++)
    {
        if (REPS[i]->frozen)
        {
            QList<QString> keys = REPS[i]->accepted.keys();
            for (int j=0; j<keys.size(); j++)
            {
                if (keys[j] == pCode)
                {
                    QStandardItem *item1 = new QStandardItem(REPS[i]->GetUsername());
                    reportsModel->setItem(currentRow, 0, item1);
                    QDate repDate = REPS[i]->GetDate();
                    QStandardItem *item2 = new QStandardItem(QString::number(repDate.year()) + "-" + QString::number(repDate.month()));
                    reportsModel->setItem(currentRow, 1, item2);
                    QStandardItem *item3 = new QStandardItem(QString::number(REPS[i]->accepted[keys[j]]));
                    reportsModel->setItem(currentRow, 2, item3);

                    currentRow++;
                    break;
                }
            }
        }
    }

    reportsModel->setHeaderData(0, Qt::Horizontal, "User");
    reportsModel->setHeaderData(1, Qt::Horizontal, "Date");
    reportsModel->setHeaderData(2, Qt::Horizontal, "Time spent");

    ui->reportsTable->resizeColumnsToContents();

    UpdateUI();
}

void ManagedProjectsDialog::EditSubmittedReport()
{
    //TO DO - ask manager about new value of time for the chosen report (QInputDialog)
}

void ManagedProjectsDialog::CloseProject()
{
    int index = ui->projectsTable->currentIndex().row();

    if (index < 0)
    {
        return;
    }

    QString pCode = model->item(index, 0)->text();
    Activities::Activity *act = Activities::GetActivity(pCode);

    if (act != nullptr)
    {
        QMessageBox messBox;
        messBox.setText("Are you sure you want to close the project?");
        messBox.setInformativeText("Users will not be able to add, edit or delete their activities for that project and you will not be able to edit submitted times for it");
        messBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        messBox.setDefaultButton(QMessageBox::No);
        int acc = messBox.exec();

        if (acc == QMessageBox::Yes)
        {
            act->active = false;

            UpdateUI();
        }
    }
}

void ManagedProjectsDialog::UpdateUI()
{
    //TO DO - update ui

    int index = ui->projectsTable->currentIndex().row();

    if (index < 0)
    {
        ui->closeProjectButton->setDisabled(true);
        ui->editTimeButton->setDisabled(true);
    }
    else
    {
        QString pCode = model->item(index, 0)->text();
        Activities::Activity *act = Activities::GetActivity(pCode);

        if (act->active)
        {
            ui->closeProjectButton->setDisabled(false);
            ui->editTimeButton->setDisabled(false);
        }
        else
        {
            ui->closeProjectButton->setDisabled(true);
            ui->editTimeButton->setDisabled(true);
        }
    }
}
