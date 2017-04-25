#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QRegExp regExp("^[1-9][0-9]{1,8}$");
    ui->SampleRate->setValidator(new QRegExpValidator(regExp, this));

}

Dialog::~Dialog()
{
    delete ui;
}
