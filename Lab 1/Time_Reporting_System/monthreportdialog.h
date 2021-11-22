#ifndef MONTHREPORTDIALOG_H
#define MONTHREPORTDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QMessageBox>

#include "jsons.h"

namespace Ui {
class MonthReportDialog;
}

class MonthReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MonthReportDialog(QWidget *parent = nullptr);
    ~MonthReportDialog();

private:
    Ui::MonthReportDialog *ui;

    QStandardItemModel *tableModel;
    QMap<QString, int> projectsTimes;

    void UpdateTable();
    void SubmitReport();
};

#endif // MONTHREPORTDIALOG_H
