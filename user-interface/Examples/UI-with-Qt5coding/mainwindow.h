#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QScrollBar>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include<QDateTime>
#include <QTimer>
#include <QMenu>
#include <QMenuBar>
#include <QAction>



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
    Ui::MainWindow *ui;
    QPushButton *Exit;
    QPushButton *Start;
    QLabel *PumpSpeed;
    QScrollBar *scrollBar;
    QSpinBox *spinBox;
    QHBoxLayout *hboxLayout;
    QGroupBox *box;
    QVBoxLayout *vbox;
    QGroupBox *box2;
    QGridLayout *gbox2;
    QPushButton *Valve1;
    QPushButton *Valve2;
    QLabel *currenttime;
    QTimer *timer;
    QMenu *help;
    QAction *Guide;
    QAction *About;

private slots:
    void timerTime();





};

#endif // MAINWINDOW_H
