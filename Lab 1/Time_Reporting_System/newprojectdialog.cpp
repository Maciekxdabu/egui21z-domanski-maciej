#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);

    connect(ui->subAddButton, &QPushButton::clicked, this, &NewProjectDialog::AddSubactivity);
    connect(ui->aubDeleteButton, &QPushButton::clicked, this, &NewProjectDialog::DeleteSubactivity);

    connect(ui->codeLine, &QLineEdit::textChanged, this, &NewProjectDialog::CheckProjectsCode);

    subcategoriesModel = new QStandardItemModel();
    ui->subactivitiesList->setModel(subcategoriesModel);

    CheckProjectsCode(ui->codeLine->text());
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;

    delete subcategoriesModel;
}

// ---------- public function

void NewProjectDialog::GetProjectData(Activities::Activity &newAct)
{
    newAct.active = true;
    newAct.manager = USER;

    newAct.code = ui->codeLine->text();
    newAct.name = ui->nameLine->text();
    newAct.budget = ui->budgetLine->text().toInt();

    newAct.subactivities.clear();
    newAct.subactivities.reserve(subcategoriesModel->rowCount());
    for (int i=0; i<subcategoriesModel->rowCount(); i++)
    {
        QString newSub = subcategoriesModel->item(i)->text();
        newAct.subactivities.append(newSub);
    }
}

void NewProjectDialog::AddSubactivity()
{
    bool ok;
    QString newSub = QInputDialog::getText(this, tr("Enter new Subcategory"), tr("Subcategory:"), QLineEdit::Normal, "", &ok);

    if (ok && !newSub.isEmpty())
    {
        QStandardItem *newSubItem = new QStandardItem(newSub);
        subcategoriesModel->appendRow(newSubItem);
    }
}

void NewProjectDialog::DeleteSubactivity()
{
    int index = ui->subactivitiesList->currentIndex().row();

    if (index >= 0)
    {
        subcategoriesModel->removeRow(index);
    }
}

void NewProjectDialog::CheckProjectsCode(QString newCode)
{
    if (newCode.isEmpty())
    {
        ui->createButton->setEnabled(false);
        return;
    }

    for (int i=0; i<ACTS.size(); i++)
    {
        if (ACTS[i].code == newCode)
        {
            ui->createButton->setEnabled(false);
            return;
        }
    }

    ui->createButton->setEnabled(true);
}
