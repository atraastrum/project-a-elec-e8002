#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, float sampleRate=0.01f, unsigned int pollingInterval_=100);
    ~Dialog();

    float sampleRate();
    unsigned int pollingInterval();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
private:
    bool testFields();

private:
    Ui::Dialog *ui;
    float m_sampleRate;
    unsigned int m_pollingInterval;
};

#endif // DIALOG_H
