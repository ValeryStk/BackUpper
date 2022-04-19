#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unordered_map>
#include <QDebug>

using um = std::unordered_map<QString,int>;
struct pages{
    const QString dashboard = "Dashboard";
    const QString backups = "Backups";
    const QString settings = "Settings";
    const QString journal = "Journal";
}pgs;

um map = {
    {"Dashboard",0},
    {"Backups",1},
    {"Settings",2},
    {"Journal",3}
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialogCreation = new DialogCreate;
    ui->stackedWidget->setCurrentIndex(map.at(pgs.dashboard));
    ui->pushButton_dashboard->setPixmap(QPixmap(":/buttons/dashboard.svg"));
    ui->pushButton_backups->setPixmap(QPixmap(":/buttons/backup.svg"));
    ui->pushButton_settings->setPixmap(QPixmap(":buttons/settings.svg"));
    ui->pushButton_history->setPixmap(QPixmap(":buttons/journal.svg"));

    ui->pushButton_dashboard->setChecked(true);
    checked = ui->pushButton_dashboard;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_dashboard_clicked()
{
    uncheckPreviousButton(ui->pushButton_dashboard);
    ui->stackedWidget->setCurrentIndex(map.at(pgs.dashboard));
}


void MainWindow::on_pushButton_backups_clicked()
{

    uncheckPreviousButton(ui->pushButton_backups);
    ui->stackedWidget->setCurrentIndex(map.at(pgs.backups));
}

void MainWindow::on_pushButton_history_clicked()
{
   uncheckPreviousButton(ui->pushButton_history);
    ui->stackedWidget->setCurrentIndex(map.at(pgs.journal));
}


void MainWindow::on_pushButton_settings_clicked()
{
    uncheckPreviousButton(ui->pushButton_settings);
    ui->stackedWidget->setCurrentIndex(map.at(pgs.settings));
}

void MainWindow::uncheckPreviousButton(QPushButton *checkedButton)
{
    if(checked != checkedButton){
        checked->setChecked(false);
        qDebug()<<"It is new button";
        checked = checkedButton;
    }else{
        checkedButton->setChecked(true);
        qDebug()<<"The same button clicked";
    }


}

void MainWindow::on_pushButton_create_backup_clicked()
{
     dialogCreation->show();
}

