#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entrydialog.h"
#include "monthreportdialog.h"
#include "managedprojectsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    entriesModel = new QStandardItemModel();
    ui->actTable->setModel(entriesModel);

    //buttons
    connect(ui->monthlyReportButton, &QPushButton::clicked, this, &MainWindow::OpenMonthlyReportDialog);
    connect(ui->projectManagementButton, &QPushButton::clicked, this, &MainWindow::OpenProjectManagementDialog);

    connect(ui->addEntButton, &QPushButton::clicked, this, &MainWindow::AddEntryButton);
    connect(ui->editEntButton, &QPushButton::clicked, this, &MainWindow::EditEntryButton);
    connect(ui->deleteEntButton, &QPushButton::clicked, this, &MainWindow::DeleteEntryButton);
    //connect(this, &MainWindow::closeEvent, this, &MainWindow::OpenProjectManagementDialog);

    //other
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &MainWindow::SetDate);

    SetDate();
}

MainWindow::~MainWindow()
{
    delete ui;

    delete entriesModel;
}

// ---------- public functions

void MainWindow::PublicUpdateData()
{
    UpdateDisplayedData();
}

// ---------- public slots

void MainWindow::OpenMonthlyReportDialog()
{
    MonthReportDialog *monthDialog = new MonthReportDialog();
    monthDialog->exec();
    delete monthDialog;
}

void MainWindow::OpenProjectManagementDialog()
{
    ManagedProjectsDialog *projectsDialog = new ManagedProjectsDialog();
    projectsDialog->exec();
    delete projectsDialog;
}

void MainWindow::AddEntryButton()
{
    EntryDialog *entryDialog = new EntryDialog();
    QDialog::DialogCode exitCode = (QDialog::DialogCode)entryDialog->exec();

    if (exitCode == QDialog::DialogCode::Accepted)
    {
        Report::Entry newEntry;
        entryDialog->LoadEntry(newEntry);
        Reports::AddEntry(newEntry);

        UpdateDisplayedData();
    }

    delete entryDialog;
}

void MainWindow::EditEntryButton()
{
    int index = ui->actTable->currentIndex().row();
    if (index < 0)
        return;

    EntryDialog *entryDialog = new EntryDialog();
    entryDialog->PushEntry(MAINREP->entries[localToGlobalIndexes[index]]);
    QDialog::DialogCode exitCode = (QDialog::DialogCode)entryDialog->exec();

    if (exitCode == QDialog::DialogCode::Accepted)
    {
        Report::Entry editEntry;
        entryDialog->LoadEntry(editEntry);
        MAINREP->entries[localToGlobalIndexes[index]] = editEntry;

        UpdateDisplayedData();
    }

    delete entryDialog;
}

void MainWindow::DeleteEntryButton()
{
    int index = ui->actTable->currentIndex().row();
    if (index < 0)
        return;

    MAINREP->entries.removeAt(localToGlobalIndexes[index]);

    UpdateDisplayedData();
}

void MainWindow::UpdateDisplayedData()
{
    Reports::ReloadCurrentReport(false);

    entriesModel->clear();
    localToGlobalIndexes.clear();

    if (MAINREP == nullptr)
    {
        ui->timeSpentLabel->setText("Time spent on activities: 0");
        return;
    }

    int gapFixer = 0;
    int timeSum = 0;
    for (int i=0; i<MAINREP->entries.size(); i++)
    {

        if (MAINREP->entries[i].date != DATE)
        {
            gapFixer++;
            continue;
        }
        localToGlobalIndexes.append(i);
        timeSum += MAINREP->entries[i].time;

        QStandardItem *newItem = new QStandardItem(MAINREP->entries[i].code);//TO DO - use project name instead of code
        entriesModel->setItem(i - gapFixer, 0, newItem);
        newItem = new QStandardItem(MAINREP->entries[i].subcode);
        entriesModel->setItem(i - gapFixer, 1, newItem);
        newItem = new QStandardItem(QString::number(MAINREP->entries[i].time));
        entriesModel->setItem(i - gapFixer, 2, newItem);
        newItem = new QStandardItem(MAINREP->entries[i].description);
        newItem->setToolTip(MAINREP->entries[i].description);
        entriesModel->setItem(i - gapFixer, 3, newItem);
    }

    entriesModel->setHeaderData(0, Qt::Horizontal, "Project");
    entriesModel->setHeaderData(1, Qt::Horizontal, "Subcode");
    entriesModel->setHeaderData(2, Qt::Horizontal, "Time");
    entriesModel->setHeaderData(3, Qt::Horizontal, "Description");

    ui->timeSpentLabel->setText("Time spent on activities: " + QString::number(timeSum));
}

void MainWindow::SetDate()
{
    DATE.setDate(ui->dateEdit->date().year(), ui->dateEdit->date().month(), ui->dateEdit->date().day());
    UpdateDisplayedData();
}
