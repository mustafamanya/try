#include "../header/execute.h"
#include "../header/parse.h"
#include "../header/connector.h"


int main(int argc, char const *argv[])
{
	char *line = NULL;
	while(true){
		cout << "$";
		line = readLine();
		if(strcmp(line,"") == 0){
			break;
		}
		parseConnectorsExecute(line);
	}
	return 0;
}