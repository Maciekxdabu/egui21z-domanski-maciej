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

    //other (updates)
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &MainWindow::SetDate);
    connect(ui->actTable, &QTableView::clicked, this, &MainWindow::UpdateInteractivity);

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

    UpdateDisplayedData();
}

void MainWindow::OpenProjectManagementDialog()
{
    ManagedProjectsDialog *projectsDialog = new ManagedProjectsDialog();
    projectsDialog->exec();
    delete projectsDialog;

    UpdateDisplayedData();
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

    if (Activities::GetActivity( MAINREP->entries[localToGlobalIndexes[index]].code )->active == false)
    {
        QMessageBox messBox;
        messBox.setWindowTitle("ProjectClosed");
        messBox.setText("You cannot edit this entry, because the project for it is already closed");
        messBox.setStandardButtons(QMessageBox::Ok);
        messBox.exec();

        return;
    }

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

    QMessageBox messBox;
    messBox.setWindowTitle("Delete?");
    messBox.setText("Are you sure you want to delete this entry?");
    messBox.setInformativeText("This action cannot be reverted");
    messBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messBox.setDefaultButton(QMessageBox::No);
    int ret = messBox.exec();

    if (ret != QMessageBox::Yes)
        return;

    if (Activities::GetActivity( MAINREP->entries[localToGlobalIndexes[index]].code )->active == false)
    {
        QMessageBox messBox;
        messBox.setWindowTitle("Delete?");
        messBox.setText("You cannot delete this entry, because the project for it is already closed");
        messBox.setStandardButtons(QMessageBox::Ok);
        messBox.exec();

        return;
    }

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
        UpdateInteractivity();
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

        QStandardItem *newItem = new QStandardItem(Activities::GetActivity(MAINREP->entries[i].code)->name + " (" + MAINREP->entries[i].code + ")");
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

    ui->actTable->resizeColumnsToContents();

    ui->timeSpentLabel->setText("Time spent on activities: " + QString::number(timeSum));

    UpdateInteractivity();
}

void MainWindow::UpdateInteractivity()
{
    Reports::ReloadCurrentReport(false);

    if (MAINREP == nullptr || MAINREP->frozen == false)
    {
        ui->addEntButton->setDisabled(false);

        if (ui->actTable->currentIndex().row() >= 0)
        {
            ui->editEntButton->setDisabled(false);
            ui->deleteEntButton->setDisabled(false);
        }
        else
        {
            ui->editEntButton->setDisabled(true);
            ui->deleteEntButton->setDisabled(true);
        }
    }
    else
    {
        ui->addEntButton->setDisabled(true);
        ui->editEntButton->setDisabled(true);
        ui->deleteEntButton->setDisabled(true);
    }
}

void MainWindow::SetDate()
{
    DATE.setDate(ui->dateEdit->date().year(), ui->dateEdit->date().month(), ui->dateEdit->date().day());
    UpdateDisplayedData();
}
