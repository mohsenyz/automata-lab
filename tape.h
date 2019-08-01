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
  virtual void moveRight();
  virtual void moveLeft();
  virtual void write(QChar);
  unsigned int currentIndex();
  unsigned int inputSize() const;
  QString toString();

protected:
  std::deque<QChar> tape;
  unsigned int _currentIndex = 0;
  unsigned int _inputSize = 0;
};

} // namespace AutomataLab

#endif // TAPE_H
