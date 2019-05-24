#include "../header/connector.h"
#include "../header/parse.h"
#include "../header/execute.h"


void parseConnectorsExecute(char *command){
	int numCmds = 0;
	char **commands = splitString(command,";",&numCmds);
	for(int i=0;i<numCmds;i++){
		commands[i] = trim(commands[i]);
		int numOrCmds = 0;
		char **orCommands = splitString(commands[i],"||",&numOrCmds);
		if(numOrCmds > 1){
			for(int j=0;j<numOrCmds;j++){
				orCommands[j] = trim(orCommands[j]);
				bool success = true;
				int numAndCmds = 0;
				char **andCommands = splitString(orCommands[j],"&&",&numAndCmds);
				for(int k=0;k<numAndCmds;k++){
					andCommands[k] = trim(andCommands[k]);
					if(!executeCommand(andCommands[k])){
						success = false;
						break;
					}
				}
				if(success){
					break;
				}
			}
		}
		else{
			int numAndCmds = 0;
			char **andCommands = splitString(commands[i],"&&",&numAndCmds);
			for(int j=0;j<numAndCmds;j++){
				andCommands[j] = trim(andCommands[j]);
				numOrCmds = 0;
				bool success = false;
				orCommands = splitString(andCommands[j],"||",&numOrCmds);
				for(int k=0;k<numOrCmds;k++){
					orCommands[k] = trim(orCommands[k]);
					if(executeCommand(orCommands[k])){
						success = true;
						break;
					}
				}
				if(!success){
					break;
				}
			}
		}
	}
}