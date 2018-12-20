/*-----------------------------------
  Actuator class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672

----------------------------------*/

#ifndef ACTUATOR_H
#define ACTUATOR_H


class Actuator{
public:
  int setState(int id);
  Actuator(int id);

Private:
  int ID, State;

protected:
};

#endif
