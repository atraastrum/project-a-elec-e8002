#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Window Resize
    this->resize(600,500);
    this->setMaximumSize(600,500);
    this->setMinimumSize(600,500);
    //Title
    this->setWindowTitle("FIA Test Bed");
    //Title bar icon
    this->setWindowIcon(QIcon(":/new/prefix1/ico"));

    // StyleSheet Setting
    this->setStyleSheet(QLatin1String("#centralWidget { \n"
    "background-color: rgba(255, 178, 133);\n"
    " }\n"
    "QPushButton\n"
    "{\n"
    "font: 87 15pt \"Arial\";\n"
    "color:white;\n"
    "border: 2px solid gray;\n"
    "border-radius: 10px;\n"
    "padding: 0 1px;\n"
    "background: rgb(0, 170, 255) ;	\n"
    "}\n"
    "QPushButton:hover {background-color: rgb(60, 255, 115); }\n"
    "\n"
    ""));

    // Exit Button
    Exit = new QPushButton(this);
    Exit->setText("Exit");
    Exit->setGeometry(QRect(100,98,81,31));
    connect(Exit,SIGNAL(clicked()),this,SLOT(close()));
    //Start Button
    Start = new QPushButton(this);
    Start->setText("Start");
    Start->setGeometry(QRect(100,57,81,31));

    //Speed Setting
    // scrollbar and pinBox
    scrollBar = new QScrollBar(this);
    spinBox = new QSpinBox(this);
    scrollBar->setOrientation(Qt::Horizontal);
    scrollBar->setGeometry(QRect(350,60,180,20));
    spinBox->setGeometry(QRect(350,90,71,31));
    scrollBar->setPageStep(10);
    connect(scrollBar,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
    connect(spinBox,SIGNAL(valueChanged(int)),scrollBar,SLOT(setValue(int)));
    scrollBar->setValue(100);
    scrollBar->setMaximum(200);
    spinBox->setMaximum(200);
    box = new QGroupBox(this);
    box->setGeometry(QRect(300,50,200,80));
    box->setTitle("Motor Speed");
    vbox = new QVBoxLayout;
    vbox->addWidget(scrollBar);
    vbox->addWidget(spinBox);
    box->setLayout(vbox);

    //Valve Choose
    box2 = new QGroupBox(this);
    box2->setGeometry(QRect(200,50,100,80));
    box2->setTitle("Valve Choose");
    gbox2 = new QGridLayout;
    Valve1 = new QPushButton(this);
    Valve1->setText("Valve1");
    Valve2 = new QPushButton(this);
    Valve2->setText("Valve2");
    gbox2->addWidget(Valve1);
    gbox2->addWidget(Valve2);
    box2->setLayout(gbox2);

    // Time Update
    currenttime = new QLabel(this);
    currenttime->setGeometry(QRect(10,450,200,25));
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerTime()));
    timer->start(1000);

    //Menu
    help = new QMenu(this);
    About = new QAction(tr( "About" ), this );
    About->setStatusTip(tr("About the FIA Test Bed" ));
    Guide = new QAction(tr( "Guide" ), this );
    Guide->setStatusTip(tr("User Guide" ));
    help = menuBar()->addMenu(tr("Help" ));
    help->addAction(Guide);
    help->addAction(About);
    menuBar()->addSeparator();







}
void MainWindow::timerTime()
{
QDateTime sysTime = QDateTime::currentDateTime();
currenttime->setText(sysTime.toString("yyyy-MM-dd-hh:mm:ss"));
}
MainWindow::~MainWindow()
{
    delete ui;
}
