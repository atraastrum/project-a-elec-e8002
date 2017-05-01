#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent, float sampleRate_, unsigned int pollingInterval_) :
    QDialog(parent),
    ui(new Ui::Dialog),
    m_sampleRate(sampleRate_),
    m_pollingInterval(pollingInterval_)
{
    ui->setupUi(this);
    QLocale locale;

    auto validatorDouble = new QDoubleValidator();
    validatorDouble->setBottom(0.0001);
    ui->SampleRate->setValidator(validatorDouble);

    auto validatorInt = new QIntValidator();
    validatorInt->setBottom(1);
    ui->PollingInterval->setValidator(validatorInt);

    ui->SampleRate->setText(locale.toString(m_sampleRate));
    ui->PollingInterval->setText(locale.toString(m_pollingInterval));
}

Dialog::~Dialog()
{
    delete ui;
}

float Dialog::sampleRate()
{
    return m_sampleRate;
}

unsigned int Dialog::pollingInterval()
{
    return m_pollingInterval;
}

void Dialog::on_pushButton_clicked()
{
    done(0);
}

void Dialog::on_pushButton_2_clicked()
{
    if (testFields())
        done(1);
}

bool Dialog::testFields()
{
    bool ok;
    QLocale locale;
    m_sampleRate    = locale.toFloat(ui->SampleRate->text(), &ok);
    m_pollingInterval = locale.toInt(ui->PollingInterval->text(), &ok);

    if (ok == false) {
        QMessageBox errorMsgBox;
        errorMsgBox.setText("The paramaters for experiment are invalid. Check them please.");
        errorMsgBox.exec();
    }

    return ok;
}
