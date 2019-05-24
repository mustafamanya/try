#pragma once

#include <iostream>
#include <cstdlib>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

bool executeCommand(char *command);
