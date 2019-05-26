#include "parse.h"
#include "execute.h"
#include <sys/stat.h>

/*function to execute a parsed Comamnd*/
bool executeCommand(char *command){
	char **args;
	int args_c,status;
	/*if command is not empty string*/
	if(strcmp(command,"")){
		if(command[0] == '[' && command[strlen(command)-1] == ']'){
			int num;
			char **tok = splitString(command,"]",&num);
			if(num != 2){
				return false;
			}
			char **tok2 = splitString(tok[0],"[",&num);
			if(num != 2){
				return false;
			}
			char cmd[512];
			strcpy(cmd,"test ");
			strcat(cmd,tok2[1]);
			return executeCommand(cmd);
		}
		/*Tokenize the command*/
		args = splitString(command," ",&args_c);
		if(strcmp(args[0],"test") == 0){
			if(args_c != 3){
				return false;
			}
			if(strcmp(args[1],"-e") == 0){
				struct stat info;
				if(lstat(args[2],&info) != 0) {
				  if(errno == ENOENT) {
				   	cout << "(False)\n";
				   } else if(errno == EACCES) {
				    cout << "(Permission denied)\n";
				   } else {
				      cout << "(Error: "<<errno << ")\n";
				   }
				  return true;
				}
				cout << "(True)\n";
			}
			else if(strcmp(args[1],"-f") == 0){
				struct stat info;
				if(lstat(args[2],&info) != 0) {
				  if(errno == ENOENT) {
				   	cout << "(False)\n";
				   } else if(errno == EACCES) {
				    cout << "(Permission denied)\n";
				   } else {
				      cout << "(Error: "<<errno << ")\n";
				   }
				  return true;
				}
				if(S_ISREG(info.st_mode)) {
					cout << "(True)\n";
				}
				else{
					cout << "(False)\n";
				}
			}
			else if(strcmp(args[1],"-d") == 0){
				struct stat info;
				if(lstat(args[2],&info) != 0) {
				  if(errno == ENOENT) {
				   	cout << "(False)\n";
				   } else if(errno == EACCES) {
				    cout << "(Permission denied)\n";
				   } else {
				      cout << "(Error: "<<errno << ")\n";
				   }
				  return true;
				}
				if(S_ISDIR(info.st_mode)) {
					cout << "(True)\n";
				}
				else{
					cout << "(False)\n";
				}
			}
			return false;
		}
		/*If the command is an exit command*/
		if(args_c == 1  && strcmp(args[0],"exit") == 0){
			// exit(1);
			kill(0,SIGTERM);
		}
		/*if the command is cd*/
		if(strcmp(args[0],"cd") == 0){
			if(args_c >= 2){
				/*Use the second argument for chdir*/
				chdir(args[1]);
				return true;
			}
		}
		/*fork a new process to execute the command*/
		if(fork() == 0){
			execvp(args[0],args);
			return false;
		}
		wait(&status);
	}
	return true;
}

