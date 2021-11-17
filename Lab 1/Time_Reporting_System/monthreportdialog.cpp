#include "monthreportdialog.h"
#include "ui_monthreportdialog.h"

MonthReportDialog::MonthReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonthReportDialog)
{
    ui->setupUi(this);
}

MonthReportDialog::~MonthReportDialog()
{
    delete ui;
}
