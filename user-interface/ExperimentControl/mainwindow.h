#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ArduinoSerial;

namespace Ui {
class MainWindow;
}

struct ExperimentSettings {
  float vInit;
  float tInit;
  float vFinal;
  float tFinal;
  float sampleRate;
  unsigned int pollingInterval;

  float totalTime() { return tInit + tFinal;}
};


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

    void on_measurementStartButton_clicked();

    void autoChangeLiquid();

private:
    void startExperiment(ExperimentSettings settings);


private:
    Ui::MainWindow *ui;
    ArduinoSerial *arduinoSerial;
    int comPortSelected = 0;

    volatile bool experimentRunning;
    QTimer* autoModeTimerForLiquids;
};

#endif // MAINWINDOW_H
