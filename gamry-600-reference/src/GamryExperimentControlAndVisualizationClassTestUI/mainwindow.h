#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  void setSignalValuesToLineEdits();
  void setDisabledSignalLineEdits(bool val = true);

private slots:
  void pollingAnimation();
  void pstatDetected();
  void on_startStopButton_clicked();
  void experimentStarted();
private:
  Ui::MainWindow *ui;
  float vInit;
  float tInit;
  float vFinal;
  float tFinal;
  float smpRate;
};

#endif // MAINWINDOW_H
