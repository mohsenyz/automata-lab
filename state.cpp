#include "state.h"

using namespace AutomataLab;

State::State() {}

State::~State() {}

State::State(QString label) : _label(label) {}

bool State::isFinal() { return final; }

bool State::isInitial() { return initial; }

void State::setInitial(bool initial) { this->initial = initial; }

void State::setFinal(bool final) { this->final = final; }

bool State::operator==(State &state) { return this->label() == state.label(); }

QString State::label() { return _label; }

void State::setLabel(QString label) { _label = label; }
