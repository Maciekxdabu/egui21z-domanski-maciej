#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entrydialog.h"
#include "menudialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    EntryDialog *edlg = new EntryDialog();
    edlg->exec();
    delete edlg;
}
