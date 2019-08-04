#ifndef STATE_H
#define STATE_H

#include "serializable.h"
#include <QString>
#include <vector>

namespace AutomataLab {

/**
 * @brief The State class, Holds automata state information
 */
class State : public Serializable {
public:
  State();
  virtual ~State();

  /**
   * @brief State Construct automata space with label
   * @param label Label of the state
   */
  explicit State(QString label);

  /**
   * @brief mark the state as initial state
   */
  void setInitial(bool);

  /**
   * @brief mark the state as final state
   */
  void setFinal(bool);

  /**
   * @brief return state label
   * @return State label
   */
  QString label();

  /**
   * @brief changes label state
   * @param label Label of state
   */
  void setLabel(QString label);

  /**
   * @brief is state initial
   * @return true if is initial
   */
  bool isInitial();

  /**
   * @brief if state final
   * @return true if is final
   */
  bool isFinal();

  /**
   * @brief operator == Checks states equality by labelname
   * @return
   */
  virtual bool operator==(State &);

  virtual void readJson(QJsonObject &) override;
  virtual void writeJson(QJsonObject &) override;

private:
  bool initial = false;
  bool final = false;
  QString _label;
};

} // namespace AutomataLab
#endif // STATE_H
