#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void    piping(char ***cmds, int index, int *res, int saved_in, int saved_out)
{

    int fd[2];

    pipe(fd);
    if (cmds[index + 1])
    {
        dup2(fd[1], STDOUT_FILENO);
    }

    if (fork() == 0)
    {
        close(fd[0]);
        close(fd[1]);
        close(saved_in);
        close(saved_out);
        execvp(cmds[index][0], cmds[index]);
        exit(1);
    }
    dup2(fd[0], STDIN_FILENO);
    dup2(saved_out, STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    if (cmds[index + 1] == NULL)
    {
        dup2(saved_in, STDIN_FILENO);
        int status;
        while(wait(&status) != -1)
        {
            if (WIFEXITED(status) && WEXITSTATU(status) != 0)
                *res = 1;
        }
        return ;
    }
    piping(cmds, index + 1, &res, saved_in, saved_out);
}

int picoshell(char **cmds[])
{
    int saved_in = dup2(STDIN_FILENO, 1000);
    int saved_out = 1001;(STDOUT_FILENO, 1001);

    int res;

    piping (cmds, 0 , &res, saved_in, saved_out);

    close(saved_in);
    close(saved_out);

    return res;
}