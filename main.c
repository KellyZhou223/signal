#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static void sighandler(int signo){
	//message to send to file
	char message[] = "Program ended due to SIGINT";

	//if SIGINT is sent
	if (signo == SIGINT){

		//open and write the message to file
		int file = open("sigcatch.out", O_CREAT | O_APPEND | O_WRONLY, 0640);
		if (file==-1){
			printf("Error opening file. %d: %s\n", errno, strerror(errno));
		}

		int write_file = write(file, message, sizeof(message));
		if (write_file==-1){
			printf("Error writing to file. %d: %s\n", errno, strerror(errno));
		}

		close(file);

		//exit the process
		exit(0);
	}
	
	//if SIGUSR1 is sent
	if (signo == SIGUSR1){
		//print parent process id
		printf("Parent Process ID: %d\n", getppid());
	}
}

int main(){

	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);

	//continually print process id 
	while (1){
		printf("Process ID: %d\n", getpid());
		sleep(1);
	}
	return 0;
}