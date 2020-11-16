/* CJshell.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define MAX_BUF 256

int getargs(char *cmd, char **argv);
void handler_SIGINT(int signo, pid_t pid);
void handler_SIGQUIT(int signo);

int main() 
{
	signal(SIGINT, handler_SIGINT);
	signal(SIGTSTP, handler_SIGQUIT);
	
	char buf[256];
	char * argv[50];
	int narg;
	pid_t pid;
	int i = 0;
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

void handler_SIGINT(int signo, pid_t pid) {
	if (kill(pid, SIGTERM) != 0) {
        	printf("\n");
    	}
}

void handler_SIGQUIT(int signo) {
	printf("\nCtrl+Z(SIGTSTP)\n");
	printf("Quit (core dumped)\n");
	
	exit(1);
}



