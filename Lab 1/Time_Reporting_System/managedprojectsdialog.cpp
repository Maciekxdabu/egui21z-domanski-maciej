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
    connect(ui->reportsTable, &QTableView::clicked, this, &ManagedProjectsDialog::UpdateUI);
    connect(ui->editTimeButton, &QPushButton::clicked, this, &ManagedProjectsDialog::EditSubmittedReport);
    connect(ui->closeProjectButton, &QPushButton::clicked, this, &ManagedProjectsDialog::CloseProject);

    model = new QStandardItemModel();
    reportsModel = new QStandardItemModel();

    ui->projectsTable->setModel(model);
    ui->reportsTable->setModel(reportsModel);

    ui->timeLeftLabel->setText("Time left for project: 0");

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
    projects.clear();

    int currentRow = 0;
    for (int i=0; i<ACTS.size(); i++)
    {
        if (ACTS[i].manager != USER)
            continue;

        projects.append(&ACTS[i]);

        QString tooltip = ACTS[i].name + " (" + ACTS[i].code + ")\nactive: " + (ACTS[i].active ? "yes\nbudget: " : "no\nbudget: ") + QString::number(ACTS[i].budget);
        for (int j=0; j<ACTS[i].subactivities.size(); j++)
        {
            tooltip += "\n  " + ACTS[i].subactivities[j];
        }
        QStandardItem *item = new QStandardItem(ACTS[i].code);
        item->setToolTip(tooltip);
        model->setItem(currentRow, 0, item);
        QStandardItem *item2 = new QStandardItem(ACTS[i].name);
        item2->setToolTip(tooltip);
        model->setItem(currentRow, 1, item2);

        currentRow++;
    }

    model->setHeaderData(0, Qt::Horizontal, "Code");
    model->setHeaderData(1, Qt::Horizontal, "Name");

    ui->projectsTable->resizeColumnsToContents();

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
    timeSum = 0;

    int currentRow = 0;
    tableReports.clear();
    for (int i=0; i<REPS.size(); i++)
    {
        if (REPS[i]->frozen)
        {
            QList<QString> keys = REPS[i]->accepted.keys();
            for (int j=0; j<keys.size(); j++)
            {
                if (keys[j] == pCode)
                {
                    tableReports.append(REPS[i]);
                    timeSum += REPS[i]->accepted[keys[j]];

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

    Activities::Activity *act = Activities::GetActivity(pCode);
    if (act->active)
        ui->timeLeftLabel->setText("Time left for project: " + QString::number(act->budget - timeSum));
    else
        ui->timeLeftLabel->setText("Time left for project: " + QString::number(act->budget));

    UpdateUI();
}

void ManagedProjectsDialog::EditSubmittedReport()
{
    int index = ui->reportsTable->currentIndex().row();

    if (index < 0)
    {
        return;
    }

    int previousValue = reportsModel->item(index, 2)->text().toInt();
    int newTime = QInputDialog::getInt(this, "New time", "Type new time for this report", previousValue, 0);

    if (newTime != previousValue)
    {
        int index2 = ui->projectsTable->currentIndex().row();
        if (index2 < 0)
            return;

        QString pCode = model->item(index2, 0)->text();
        QList<QString> keys = tableReports[index]->accepted.keys();
        for (int i=0; i<keys.size(); i++)
        {
            if (keys[i] == pCode)
            {
                tableReports[index]->accepted[keys[i]] = newTime;
                break;
            }
        }
    }

    UpdateSelectedProject();
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
        messBox.setWindowTitle("Close project?");
        messBox.setText("Are you sure you want to close the project?");
        messBox.setInformativeText("Users will not be able to add, edit or delete their activities for that project and you will not be able to edit submitted times for it");
        messBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        messBox.setDefaultButton(QMessageBox::No);
        int acc = messBox.exec();

        if (acc == QMessageBox::Yes)
        {
            act->active = false;
            act->budget -= timeSum;

            UpdateUI();
        }
    }
}

void ManagedProjectsDialog::UpdateUI()
{
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

            int index2 = ui->reportsTable->currentIndex().row();
            if (index2 < 0)
                ui->editTimeButton->setDisabled(true);
            else
                ui->editTimeButton->setDisabled(false);
        }
        else
        {
            ui->closeProjectButton->setDisabled(true);
            ui->editTimeButton->setDisabled(true);
        }
    }
}
