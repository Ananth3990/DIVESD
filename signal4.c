#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void sigchld_handler(int sig)
{
	int status, ret;
	ret = waitpid(-1, &status, 0);
	if(ret!=-1)
		printf("child exit val : %d\n", WEXITSTATUS(status));
}

int main()
{
	int ret, i;
	struct sigaction sa;
	
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigchld_handler;
	ret = sigaction(SIGCHLD, &sa, NULL);
	// err check
	
	printf("program starts!\n");
	ret = fork();
	printf("fork() returned : %d\n", ret);
	if(ret==0) // child
	{
		for(i=0; i<10; i++)
		{
			printf("child : %d\n", i);
			sleep(1);
		}
		_exit(4);
	}
	else // parent
	{
		for(i=0; i<20; i++)
		{
			printf("parent : %d\n", i);
			sleep(1);
		}
	}
	printf("program ends!\n");
	return 0;	
}

