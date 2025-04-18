#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void PublicUpdateData();//called from main after username is inputed

private slots:
    //for buttons
    void OpenProjectManagementDialog();
    void OpenMonthlyReportDialog();

    void AddEntryButton();
    void EditEntryButton();
    void DeleteEntryButton();
    void UpdateDisplayedData();

    void UpdateInteractivity();

    void SetDate();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *entriesModel;

    QVector<int> localToGlobalIndexes;
};
#endif // MAINWINDOW_H
