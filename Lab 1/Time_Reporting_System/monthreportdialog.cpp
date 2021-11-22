#include "monthreportdialog.h"
#include "ui_monthreportdialog.h"

MonthReportDialog::MonthReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonthReportDialog)
{
    ui->setupUi(this);

    connect(ui->submitButton, &QPushButton::clicked, this, &MonthReportDialog::SubmitReport);

    tableModel = new QStandardItemModel();
    ui->timeTable->setModel(tableModel);

    UpdateTable();
}

MonthReportDialog::~MonthReportDialog()
{
    delete ui;
}

void MonthReportDialog::UpdateTable()
{
    tableModel->clear();

    Reports::ReloadCurrentReport(false);

    projectsTimes.clear();

    if (MAINREP == nullptr || MAINREP->entries.size() == 0)
    {
        ui->submitButton->setDisabled(true);

        return;
    }
    else if (MAINREP->frozen)
        ui->submitButton->setDisabled(true);
    else
        ui->submitButton->setDisabled(false);

    for (int i=0; i<MAINREP->entries.size(); i++)
    {
        if (projectsTimes.contains(MAINREP->entries[i].code))
            projectsTimes[MAINREP->entries[i].code] += MAINREP->entries[i].time;
        else
            projectsTimes.insert(MAINREP->entries[i].code, MAINREP->entries[i].time);
    }

    QList<QString> keys = projectsTimes.keys();
    for (int i=0; i<keys.size(); i++)
    {
        QStandardItem *item1 = new QStandardItem(Activities::GetActivity(keys[i])->name + " (" + keys[i] + ")");
        tableModel->setItem(i, 0, item1);
        QStandardItem *item2 = new QStandardItem(QString::number(projectsTimes[keys[i]]));
        tableModel->setItem(i, 1, item2);
    }

    tableModel->setHeaderData(0, Qt::Horizontal, "Project");
    tableModel->setHeaderData(1, Qt::Horizontal, "Time Spent");

    ui->timeTable->resizeColumnsToContents();
}

void MonthReportDialog::SubmitReport()
{
    QMessageBox messBox;
    messBox.setWindowTitle("Submit report?");
    messBox.setText("Are you sure you want to submit current month's report?\n");
    messBox.setInformativeText("You will not be able to add or edit any entries for this month afterwards");
    messBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messBox.setDefaultButton(QMessageBox::No);
    int accept = messBox.exec();

    if (accept == QMessageBox::Yes)
    {
        MAINREP->frozen = true;

        MAINREP->accepted.clear();
        QList<QString> keys = projectsTimes.keys();
        for (int i=0; i<keys.size(); i++)
        {
            MAINREP->accepted.insert(keys[i], projectsTimes[keys[i]]);
        }

        ui->submitButton->setDisabled(true);
    }
}
