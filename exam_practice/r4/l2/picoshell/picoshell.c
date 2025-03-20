/* TASK:
Allowed functions: close, fork, wait, exit, execvp, dup2, pipe
--------------------------------------------------------------------------------
Write the followingfunction

int picoshell(char **cmds[]);

The goal of this function is to execute a pipeline.
It must execute each commands of cmds and connect the output of one to the input
of the next command (just like a shell)

Cmds contains a null-terminated list of valid commands.
Each rows of cmds are an argv array directly useable for a call to execvp.
The first arguments of each command is the command name or path and can be
passed directly as the first argument of execvp.

If any error occur, the function must return 1 (you must of course close all the
open fds before), otherwise the function must wait all child processes and return 0

You will find in this directory a file main.c which contain something to help you
test your function.

For example this should work:
$>./picoshell /bin/ls "|" /usr/bin/grep picoshell
picoshell

$>./picoshell echo 'squalala!' "|" cat "|" sed 's/a/b/g'
squblblb!

Hints:
Do not leak file descriptors
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void piping(char ***cmds, int index, int *res, int saved_stdin, int saved_stdout)
{
	int fd[2];

	pipe(fd);
	if (cmds[index + 1])
		dup2(fd[1], STDOUT_FILENO);
	if (fork() == 0)
	{
		close(fd[0]);
		close(fd[1]);
		close(saved_stdin);
		close(saved_stdout);
		execvp(cmds[index][0], cmds[index]);
		exit(1);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (cmds[index + 1] == NULL)
	{
		dup2(saved_stdin, STDIN_FILENO);
		int status;
		while (wait(&status) != -1)
		{
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
                *res = 1;
		}
		return ;
	}
	piping(cmds, index + 1, res, saved_stdin, saved_stdout);
}

int picoshell(char **cmds[])
{
	int saved_stdin = dup2(STDIN_FILENO, 1000);
	int saved_stdout = dup2(STDOUT_FILENO, 1001);
	int res = 0;

	piping(cmds, 0, &res, saved_stdin, saved_stdout);

	close(saved_stdin);
	close(saved_stdout);

	return (res);
}

/* int main(int argc, char **argv)
{
	int cmd_size = 1;

	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "|"))
			cmd_size++;
	}

	char ***cmds = calloc(cmd_size + 1, sizeof(char ***));
	cmds[0] = argv + 1;
	int cmds_i = 1;
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "|"))
		{
			cmds[cmds_i] = argv + i + 1;
			argv[i] = NULL;
			cmds_i++;
		}
	}
	int ret = picoshell(cmds);
	if (ret)
		perror("picoshell");
	free(cmds);
	return ret;
} */