#ifndef STATE_H
#define STATE_H

#include <QString>
#include <vector>

namespace AutomataLab{

class State
{
public:
    State();
    explicit State(QString label);

    void setInitial(bool);
    void setFinal(bool);
    QString label();
    void setLabel(QString label);
    bool isInitial();
    bool isFinal();
    bool operator== (State&);
private:
    bool initial;
    bool final;
    QString _label;
};


}
#endif // STATE_H
