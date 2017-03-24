#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
  Ui::MainWindow *ui;
  Gamry::QPotentiostat* rpPstat;
};

#endif // MAINWINDOW_H
