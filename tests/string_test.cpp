#include <iostream>
#include <string>

using namespace std;

char numbers[] = {-127, 'H', -11, '0', 42};
string s(numbers);
int main(){
	//~ for(char i: numbers){
		//~ s += i;
		//~ }
	for(char i: s){
		cout << to_string(i) << ", ";
		}
	cout << endl;
	//~ cout << to_string(s);
	}
