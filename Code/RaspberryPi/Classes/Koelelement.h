/*-----------------------------------
  Koelelement class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef KOELELEMENT_H
#define KOELELEMENT_H


class Koelelement{
public:
  Koelelement(int ID,int Temp);
private:
  int ID, Temp;
  bool On;
protected:
};

#endif
