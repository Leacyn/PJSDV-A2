#include "formInfo.h"
#include <regex>

formInfo::formInfo(std::string path){
	jsonFilePath = path;
}

formInfo::renew(){
	std::string subject;
 	std::ifstream myfile ("output.json");
  	if (myfile.is_open()){
  		while ( getline (myfile,subject) ){
			try {
  				std::regex re("{\"A\":\"(\\S*?)\",\"B\":\"(\\S*?)\",\"C\":\"(\\S*?)\"}");
  				std::sregex_iterator next(subject.begin(), subject.end(), re);
  				std::sregex_iterator end;
  				while (next != end) {
    				std::smatch match = *next;
    				std::cout << match.str() << "\n";
    				next++;
  				} 
			} catch (std::regex_error& e) {
  				std::cout << "Syntax error in the regular expression";
			}
    	}
    	myfile.close();
  	}
	else std::cout << "Unable to open file"; 
}

struct attribute formInfo::getAttribute(int i){
	return attributes.find(i)->second;
}

