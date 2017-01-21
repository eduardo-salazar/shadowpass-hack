#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>

/**********************************************************/
/* You can not modify the code in this block */
/* You can not modify the code in this block */
/* You can not modify the code in this block */
void execUserCommand(){
	char* arg[] = {"sleep", "2", NULL};
	if ( execvp(arg[0],arg) < 0 ){
	    fprintf(stderr,"%s : command not found\n",arg[0]);
	    exit(1);
	}
}
/**********************************************************/


int main(void) {

	/*The following code may cause zombie*/
	//child process
	pid_t pid;
	if ((pid = fork()) < 0) {
		fprintf(stderr,"fork error");
	} else if (pid == 0) {
		if ((pid = fork()) < 0)
			perror("fork error");
		else if (pid > 0)
			exit(0); /* parent from second fork == first child */
		/* child process*/
		execUserCommand();
		exit(0);
	}

	/* parent */
	sleep(4);
	/* parent doesn't wait for the child but it may lead to zombie */
	printf("After execuation\n");
	system("ps -o pid,ppid,state,tty,command");

	exit(0);
}
