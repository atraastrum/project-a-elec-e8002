#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ArduinoSerial;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow(); 

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void on_startPumpButton_clicked();

    void on_comPortSelect_valueChanged(int arg1);

    void on_comPortSelection_clicked();

    void on_modeSelection_activated(const QString &arg1);

    void on_liquid1Control_clicked();

    void on_liquid2Control_clicked();
    void Setup();

    void on_controlPSTATButton_clicked();

    void checkIfDone();

private:
    void startExperiment();

private:
    Ui::MainWindow *ui;
    ArduinoSerial *arduinoSerial;
    int comPortSelected = 0;

    volatile bool experimentRunning;
};

#endif // MAINWINDOW_H
