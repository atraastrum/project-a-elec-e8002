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

  signals:

  public slots:
  private:
    Potentiostat* rpPstat;
  };
}


#endif // QPOTENTIOSTAT_HPP
