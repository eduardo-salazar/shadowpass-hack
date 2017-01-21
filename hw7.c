#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>


int main(void) {
	printf("Begin of process..\n");
	pid_t pid;
	if ((pid = fork()) < 0) {
		fprintf(stderr,"fork error");
	} else if (pid == 0) {
		printf("I am a child with pid %d and pgid %d\n",(int)getpid(),(int)getpgid(getpid()));
		exit(0);
		// pid_t new = setsid();
		// if (new < 0)
		// 	perror("setsid error");
	}
	wait(NULL);
	printf("Parent Finishing with pid %d and pgid %d\n",(int)getpid(),(int)getpgid(getpid()));
	exit(0);
}
