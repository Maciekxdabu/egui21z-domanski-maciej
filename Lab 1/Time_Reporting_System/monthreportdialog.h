#ifndef MONTHREPORTDIALOG_H
#define MONTHREPORTDIALOG_H

#include <QDialog>

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
};

#endif // MONTHREPORTDIALOG_H
