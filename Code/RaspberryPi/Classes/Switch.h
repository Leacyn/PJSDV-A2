/*-----------------------------------
  Switch class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef SWITCH_H
#define SWITCH_H


class Switch: Public Device{
Public:

  Switch(int id);
  int checkState(int id);
  int changeState(int id, int value);
private:
  int ID;
  int State;
Protected:

}

#endif
