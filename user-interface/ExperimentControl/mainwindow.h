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

private slots:
    void on_startPumpButton_clicked();

    void on_liquid1Button_clicked();

    void on_liquid2Button_clicked();

private:
    Ui::MainWindow *ui;
    ArduinoSerial *arduinoSerial;
};

#endif // MAINWINDOW_H
