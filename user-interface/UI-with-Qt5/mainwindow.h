#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDateTime>
#include <QTimer>
#include <QLabel>
#include<ui_mainwindow.h>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private:
    Ui::MainWindow ui;
    QLabel *currenttime;
    QTimer *timer;
private slots:
    void timerTime();
};

#endif // MAINWINDOW_H
