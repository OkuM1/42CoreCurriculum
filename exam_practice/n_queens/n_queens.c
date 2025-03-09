/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:21:36 by mokutucu          #+#    #+#             */
/*   Updated: 2025/03/09 16:17:43 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_queens.h"

int safe_qpos(int *arr, int column, int row)
{
    int i = 0;
    
    while (i < column)
    {
        if (arr[i] == row) //same row check
			return (0);
		if (arr[i] - i == row - column) //left to right diagonal
			return (0);
		if (arr[i] + i == row + column) //right to left diagonal
			return (0);
		i++;
	}
	return (1);
}
void print_solution(int *arr, int n)
{
    int i = 0;

    while (i < n)
    {
        if (i == 0)
            printf("%d", arr[i]);
        else
            printf(" %d", arr[i]);
        i++;
    }
    printf("\n");
}

void solve(int n, int *arr, int column)
{
    int i = 0;

    if (column == n)
    {
        print_solution(arr, n);
        return;
    }
    while (i < n)
    {
        if (safe_qpos(arr, column, i))
        {
            arr[column] = i;
            solve(n, arr, column + 1);
        }
        i++;
    }
}
int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    int n = atoi(av[1]);
    if (n < 1)
        return (1);
    int arr[n];

    solve(n, arr, 0);

    return (0);
}