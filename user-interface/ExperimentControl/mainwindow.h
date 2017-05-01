#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamry.hpp"

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
  float delay;

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
    // Creates Setup Dialog when Menu item is triggered
    void Setup();

    void on_startPumpButton_clicked();

    void on_comPortSelect_valueChanged(int arg1);

    void on_comPortSelection_clicked();

    void on_modeSelection_activated(const QString &arg1);

    void on_liquid1Control_clicked();

    void on_liquid2Control_clicked();

    void on_controlPSTATButton_clicked();

    void checkIfDone();

    void on_measurementStartButton_clicked();

    void autoChangeLiquid();

    void waitForPstatToInitializeAndStart();

    void waitForDelay();


    void addItemsToDataTable();

    void on_saveDataButton_clicked();


private:
    void startExperiment(ExperimentSettings settings);


private:
    Ui::MainWindow *ui;
    ArduinoSerial *arduinoSerial;
    int comPortSelected = 0;

    volatile bool experimentRunning;
    volatile bool m_pstatInitialized;
    volatile bool m_delayTimeOut;
    QTimer* autoModeTimerForLiquids;

    unsigned int m_aemDotCount; // Active Experiment message animation
    float m_autoVoltage;
    float m_autoTime;
    float m_autoInterval;
    float m_autoDelay;
    int m_lastSizeBeforeAddToTable;

    float m_manualVinit;
    float m_manualTinit;
    float m_manualVfinal;
    float m_manualTfinal;

    float m_pstatSettingsSampleRate;
    unsigned int m_pstatSettingsPollingInterval;

    QVector<Gamry::CookInformationPoint> allDataFromPstat;

};

#endif // MAINWINDOW_H
