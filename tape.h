#ifndef TAPE_H
#define TAPE_H

#include <QChar>
#include <QString>
#include <deque>

#define BLANK_CHARACTER '#'

namespace AutomataLab {

class Tape {
public:
  explicit Tape(QString);
  QChar read();
  void moveRight();
  void moveLeft();
  void write(QChar);
  QString toString();

protected:
  std::deque<QChar> tape;
  unsigned int currentIndex;
};

} // namespace AutomataLab

#endif // TAPE_H
