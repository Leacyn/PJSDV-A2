#include <cstdlib>
#include <stdio.h>
#include "formInfo.cpp"


#define DataPath "output.json"

int main(void){
	formInfo json (DataPath);
	json.renew();
	
}
