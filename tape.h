#ifndef TAPE_H
#define TAPE_H

#include <QChar>
#include <QString>
#include <deque>

#define BLANK_CHARACTER '#'

namespace AutomataLab {

/**
 * @brief The Tape class
 */
class Tape {
public:
  /**
   * Construct tape from input string
   */
  explicit Tape(QString);

  /**
   * @brief Reads current character from tape
   * @return
   */
  QChar read();

  /**
   * @brief Moves tape head to right
   */
  virtual void moveRight();

  /**
   * @brief Moves tape head to left
   */
  virtual void moveLeft();

  /**
   * @brief Writes a character to current head
   */
  virtual void write(QChar);

  /**
   * @brief Returns head index in deque
   * @return
   */
  unsigned int currentIndex();

  /**
   * @brief Returns user entered input size
   * @return
   */
  unsigned int inputSize() const;

  /**
   * @brief Converts tape to string
   * @return
   */
  QString toString();

protected:
  std::deque<QChar> tape;
  unsigned int _currentIndex = 0;
  unsigned int _inputSize = 0;
};

} // namespace AutomataLab

#endif // TAPE_H
