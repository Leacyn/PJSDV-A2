#include <iostream>
#include <cstring>
#include <string>



using namespace std;

struct test
{
	int one;
	int two;
	char text[128];
	
};

void serialise(struct test&, char *);
void deserialise(char*, struct test&);

int main(int argc, char** argv){

	char data[256];

	test testing;
	testing.one = 1;
	testing.two = 15;
	strcpy(testing.text,"this is a message");

	serialise(testing, data);

	testing.one = 0;
	testing.two = 0;
	strcpy(testing.text, "");

	deserialise(data, testing);
	cout << testing.one+1 << endl;
	cout << testing.two+1 << endl;
	cout << testing.text << endl;

}




void serialise(struct test &testtmp, char *data){
	int *temp = (int *)data;
//	temp = malloc(sizeof(struct test));

	*temp = testtmp.one; 	temp++;
	*temp = testtmp.two;	temp++;

	char *p = (char*)temp;
    int i = 0;
    while (i < 128)
    {
        *p = testtmp.text[i] ;
        p++;
        i++;
    }
}


void deserialise(char *data, struct test &temp){

	int *q = (int *)data;

	temp.one = *q;		q++;
	temp.two = *q;		q++;

	char *p = (char *)q;
	int i = 0;

	while(i < 128){

		temp.text[i] = *p;
		p++;
		i++;

	}


}



