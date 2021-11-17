#include "entrydialog.h"
#include "ui_entrydialog.h"

EntryDialog::EntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDialog)
{
    ui->setupUi(this);

    Initialize();
    RefreshSubcategories();

    connect(ui->projectCombo, &QComboBox::currentIndexChanged, this, &EntryDialog::RefreshSubcategories);
}

EntryDialog::~EntryDialog()
{
    delete ui;
}

void EntryDialog::LoadEntry(Report::Entry &newEntry)
{
    newEntry.date = DATE;
    newEntry.code = ACTS[Activities::GetActiveProjectIndex(ui->projectCombo->currentIndex())].code;
    newEntry.subcode = ui->subCatCombo->currentText();
    newEntry.time = ui->timeLine->text().toInt();
    newEntry.description = ui->descText->toPlainText();
}

void EntryDialog::PushEntry(Report::Entry &pushEntry)
{
    int activeIndex = 0;
    for (int i=0; i<ACTS.size(); i++)
    {
        if (ACTS[i].active)
        {
            if (ACTS[i].code == pushEntry.code)
            {
                ui->projectCombo->setCurrentIndex(activeIndex);

                for (int j=0; j<ACTS[i].subactivities.size(); j++)//looking for subactivities
                {
                    if (ACTS[i].subactivities[j] == pushEntry.subcode)
                    {
                        ui->subCatCombo->setCurrentIndex(j+1);
                    }
                }

                break;
            }

            activeIndex++;
        }
    }

    ui->timeLine->setText(QString::number(pushEntry.time));
    ui->descText->setText(pushEntry.description);
}

void EntryDialog::Initialize()
{
    for (int i=0; i<ACTS.size(); i++)
    {
        if (ACTS[i].active)
            ui->projectCombo->insertItem(i, ACTS[i].name + " (" + ACTS[i].code + ")");
    }
}

void EntryDialog::RefreshSubcategories()
{
    int projectIndex = Activities::GetActiveProjectIndex(ui->projectCombo->currentIndex());

    ui->subCatCombo->clear();
    ui->subCatCombo->insertItem(0, "");
    for (int i=0; i<ACTS[projectIndex].subactivities.size(); i++)
    {
        ui->subCatCombo->insertItem(i+1, ACTS[projectIndex].subactivities[i]);
    }
}
