#ifndef QPOTENTIOSTAT_HPP
#define QPOTENTIOSTAT_HPP

#include <QObject>
namespace Gamry {
  class Potentiostat;
  class QPotentiostat : public QObject
  {
    Q_OBJECT

  public:
    explicit QPotentiostat(QObject *parent = 0);
    ~QPotentiostat();

  protected:
    void timerEvent(QTimerEvent *event);

  signals:
    void detected();

  public slots:
  private:
    Potentiostat* rpPstat;
    int iTimerIDDevCount;
  };
}


#endif // QPOTENTIOSTAT_HPP
