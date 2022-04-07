#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <DialogCreate.h>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_dashboard_clicked();
    void on_pushButton_backups_clicked();
    void on_pushButton_history_clicked();
    void on_pushButton_settings_clicked();

    void on_pushButton_create_backup_clicked();

private:
    Ui::MainWindow *ui;
    DialogCreate *dialogCreation;
    QPushButton *checked;
    void uncheckPreviousButton(QPushButton *checkedButton);
};
#endif // MAINWINDOW_H
