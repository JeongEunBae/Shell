/* jeongeunshell.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include "shell_signal.h"
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 256

int getargs(char *cmd, char **argv);

int main() 
{
	sigInt();
	sigQuit();
	
	char buf[256];
	char * argv[50];
	int narg;
	pid_t pid;
	
	while(1) {
		printf("CJshell >> ");
		
		gets(buf);
		
		if(strcmp(buf, "exit") == 0) {
			printf("finish CJshell :(\n");
			exit(0);
		}
		
		narg = getargs(buf, argv);
		
		pid = fork();
		
		if(pid == 0 ) {
			execvp(argv[0], argv);
		}
		else if (pid > 0)
			wait((int*)0);
		else
			perror("fork failed");
	}
}

int getargs(char *cmd, char ** argv) 
{
	int narg = 0;
	
	while(*cmd) {
		if(*cmd == ' ' || *cmd == '\t')
			*cmd ++ = '\0';
		else {
			argv[narg++] = cmd++;
			while(*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
				cmd++;
		}
	}
	argv[narg] = NULL;
	return narg;
}
