#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string s, char c)
{
	string temp = "";
	vector<string> v;
	
	for(int i = 0; i < s.length(); ++i)
	{
		if(s[i] != c) {
			temp+=s[i]; 
		}
		else if(s[i] == c && temp != "") {
			v.push_back(temp); 
			temp = ""; 
		}
	}
	if(temp != "") {
		v.push_back(temp);
	}
	return v;
}

int runShell() {
	cout << "Welcome to J_Bash." << endl;
	
	while(true) {
		char *newBuffer = NULL;
		string userInput;
		cout << ">> ";

		getline(cin,userInput);
		
		if (userInput == "exit") {
			break;
		}

		vector<string> splitString = split(userInput,' ');

		char **args = new char *[splitString.size() + 1];

		for(int i = 0; i < splitString.size(); ++i) {
			args[i] = const_cast<char*>(splitString[i].c_str());
		}
		
		args[splitString.size()] = (char *) 0;

		pid_t pid;
		pid = fork();
		if(pid<0){
		   fprintf(stderr, "fork failed");
		   return 1;    
		}
		else if(pid == 0){  

			char * bin = "/bin/";
			newBuffer = new char[strlen(args[0])+6];
			strcpy(newBuffer,bin);
			strcat(newBuffer,args[0]);
			/*cout << newBuffer << endl;

			for(int i = 0; i < splitString.size() + 1; ++i) {
				cout << args[i] << endl;
			}*/
			//execlp("/bin/touch","hello.txt",)

			execv(newBuffer,args);
		}
		else{
		   wait(NULL);
		   printf("child complete\n");
		}

		if(newBuffer != NULL) {
			cout << pid << endl;
			delete newBuffer;
		}

		delete[] args;
	}

	return 0;
}

int main(){

	return runShell();
	
}