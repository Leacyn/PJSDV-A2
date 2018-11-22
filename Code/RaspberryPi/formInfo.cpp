#include "formInfo.h"
#include <regex>

formInfo::formInfo(std::string path){
	jsonFilePath = path;
}

formInfo::renew(){
	std::string line;
 	std::ifstream myfile ("output.json");
  	if (myfile.is_open()){
  		
  		std::string subject("This is a test");
		try {
  			std::regex re("\\w+");
  			std::sregex_iterator next(subject.begin(), subject.end(), re);
  			std::sregex_iterator end;
  			while (next != end) {
    			std::smatch match = *next;
    			std::cout << match.str() << "\n";
    			next++;
  			} 
		} catch (std::regex_error& e) {
  // Syntax error in the regular expression
	}



    	while ( getline (myfile,line) ){
    		std::regex key("{\"A\":\"(\\S*?)\",\"B\":\"(\\S*?)\",\"C\":\"(\\S*?)\"}");
      		std::cout << line << '\n';
    	}
    	myfile.close();
  	}
	else std::cout << "Unable to open file"; 
}

struct attribute formInfo::getAttribute(int i){
	return attributes.find(i)->second;
}

