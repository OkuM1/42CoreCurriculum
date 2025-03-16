/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:36:26 by mokutucu          #+#    #+#             */
/*   Updated: 2025/03/16 14:11:17 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TASK:
Name: ft_popen
Allowed functions: pipe, fork, dup2, execvp, close, exit
--------------------------------------------------------------------------------
Write the following function:

int ft_popen(const char *file, const char *argv[], char type);

The function must launch the executable file with the arguments argv (using execvp).
If type is 'r' the function must return a file descriptor connected to the output of the command.
If type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

For example the function could be used like that:

int main()
{
    int fd = ft_popen("ls", (const char *[]) {"ls", NULL}, 'r');
    char *line;
    while ((line = get_next_line(fd)))
        ft_putstr(line);
}

Hints:
Do not leak file descriptors.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;

	int fd[2];
	int status;

	pipe(fd);
	if (type == 'r')
	{
		if (fork() == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit (-1);
		}
		close(fd[1]);
		return (fd[0]);
	}
	if (type == 'w')
	{
		if (fork() == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit (-1);
		}
		close(fd[0]);
		return (fd[1]);
	}
	return -1;
}

int main()
{
    int fd = ft_popen("wc", (char *const[]){"wc", NULL}, 'w');
	if (fd == -1)
	{
		perror("error ft_popen args");
		return (0);
	}

    char *input = "Hello world\nThis is a test\nthird line\n";
    write(fd, input, strlen(input));
	

    close(fd);
	printf("after test\n");
    return (0);
} 

/* int main()
{
    // Use ft_popen to run "ls" and read its output
    int fd = ft_popen("ls", (char *[]){"ls", NULL}, 'r');
    if (fd == -1)
    {
        perror("ft_popen");
        return 1;
    }

    // Read and print the output of the "ls" command
    char buffer[128];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
    }

    close(fd);
    return 0;
} */