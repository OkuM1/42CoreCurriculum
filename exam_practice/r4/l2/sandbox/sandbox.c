#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void do_nothing(int sig)
{
	(void)sig;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		alarm(timeout);
		f();
		exit(0);
	}
	struct sigaction sa;
	sa.sa_handler = do_nothing;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGALRM, &sa, NULL);

	alarm(timeout);

	int status;
	pid_t r = waitpid(pid, &status, 0);
	if (r == -1)
	{
		if (errno == EINTR)
		{
            printf("waitpid");
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0);
		}
		return (-1);
	}
	if (WIFEXITED(status))
	{
		int ex_code = WEXITSTATUS(status);
		if (ex_code == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		printf("Bad function: exited with code %d\n", ex_code);
		return (0);
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGALRM)
		{
            printf("signal");
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0);
		}
		if (verbose)
			printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
		return (0);
	}
	return (-1);
}

void ok_f(void)
{
    printf("Nice function running...\n");
}

void inf_f(void)
{
    while (1);
}

void bad_exit(void)
{
    exit(42);
}

void leak_f(void)
{
    int *p = NULL;
    *p = 4;
}

int main(void)
{
    //printf("\n--- Testing a normal function ---\n");
    //sandbox(ok_f, 3, true); // Should print "Nice function!"

    //printf("\n--- Testing an infinite loop function ---\n");
    //sandbox(inf_f, 2, true); // Should print "Bad function: timed out"

    //printf("\n--- Testing a function with a bad exit code ---\n");
    //sandbox(bad_exit, 3, true); // Should print "Bad function: exited with code 42"

    //printf("\n--- Testing a function that causes a segmentation fault ---\n");
    //sandbox(leak_f, 3, true); // Should print "Bad function: Segmentation fault" or similar

    return 0;
}