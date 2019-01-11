#include "Domotica.h"

/*Define SQL login data*/
#define DBPATH "tcp://127.0.0.1:3306"
#define USER "editor"
#define PASSWD "100%Domotics"
#define DB "domotics"

/*start setup and loop
1. The main program starts with the setup
2. Loop runs continiously
Both defined in Domotica
*/
int main(int argc, char** argv){
  Domotica dom(DBPATH, USER, PASSWD, DB);
  if(dom.setup())
    return dom.loop();
  else
    return 0;
}
