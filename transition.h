#ifndef TRANSITION_H
#define TRANSITION_H

#include "serializable.h"
#include "state.h"
#include <QChar>
#include <vector>

namespace AutomataLab {

/**
 * @brief The Transition class, Holds automata transition informations
 */
class Transition : public Serializable {
public:
  /**
   * @brief Construct transition from a state to a state
   * @param State * form state
   * @param State * to state
   */
  Transition(State *, State *);

  /**
   * @brief Construct transition from a state to a state, with multiple
   * accepting character
   * @param State * form state
   * @param State * to state
   * @param std::vector<QChar> accepted characters
   */
  Transition(State *, State *, std::vector<QChar>);

  /**
   * @brief Construct transition from a state to a state. with single accepting
   * character
   * @param State * from state
   * @param State * to state
   * @param QChar accepted character
   */
  Transition(State *, State *, QChar);
  virtual ~Transition();

  /**
   * @brief Checks if transition accepts a single character
   * @param QChar character to check
   * @return returns true if transtion accept character
   */
  bool accepts(QChar);

  /**
   * @brief List all of accepted inputs
   * @return
   */
  std::vector<QChar> acceptInputs();

  /**
   * @brief Sets list of accepted inputs
   * @warning It doesn't append, it sets
   */
  void setAcceptInputs(std::vector<QChar>);

  /**
   * @brief Sets a single accepted character
   * @warning It doesn't append chracter, it sets
   */
  void setAcceptInput(QChar);

  /**
   * @brief Returns from state
   * @return
   */
  State *fromState();

  /**
   * @brief Returns to state
   * @return
   */
  State *toState();

  /**
   * @brief operator == Check to transitions equality
   * @return
   */
  virtual bool operator==(Transition &);

  virtual void readJson(QJsonObject &) override;
  virtual void writeJson(QJsonObject &) override;

private:
  State *_fromState;
  State *_toState;
  std::vector<QChar> _acceptedInputs;
};

} // namespace AutomataLab

#endif // TRANSITION_H
