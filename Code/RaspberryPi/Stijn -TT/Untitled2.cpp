#include <cstdlib>
#include <stdio.h>
#include "formInfo.h"


#define DataPath "output.json"

int main(void){
	formInfo json (DataPath);
	json.renew();
	
}
