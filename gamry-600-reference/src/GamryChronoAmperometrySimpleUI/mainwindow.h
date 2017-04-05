#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamry.hpp"

namespace Ui {
class MainWindow;
}

namespace Gamry {
class QPotentiostat;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
  void activateButton();

private slots:
  void on_startExperButton_clicked();
  void updatePlot(std::vector<Gamry::CookInformationPoint>);

private:
  Ui::MainWindow *ui;
  Gamry::QPotentiostat* rpPstat;
  float fTotalExperimentTime;
};

#endif // MAINWINDOW_H
