#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler_sigint(int signo) {
	printf("Ctrl+C(SIGINT) On\n");
	
	pid_t ppid = getppid();
	kill(ppid, SIGINT);
}

void handler_sigquit(int signo) {
	printf("Ctrl+Z(SIGTSTP) On\n");
	printf("Quit (core dumped)\n");
	
	pid_t ppid = getppid();
	kill(ppid, SIGQUIT);
}

void sigInt() 
{
	struct sigaction sigint;

	sigint.sa_handler = handler_sigint;
	
	sigfillset(&(sigint.sa_mask));
	sigaction(SIGINT, &sigint, NULL);
	
}

void sigQuit() 
{
	struct sigaction sigquit;

	sigquit.sa_handler = handler_sigquit;
	
	sigfillset(&(sigquit.sa_mask));
	sigaction(SIGTSTP, &sigquit, NULL);
	
	/*int i =0 ;
	while(1) {
		sleep(1);
		printf("sleep for %d sec(s). \n", ++i);
	}*/
}

