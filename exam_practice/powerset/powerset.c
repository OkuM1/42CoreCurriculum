/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:07:04 by mokutucu          #+#    #+#             */
/*   Updated: 2025/03/09 14:25:50 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "powerset.h"

int sum_check(int x, int *subset, int len)
{
    int sum = 0;
    int i = 0;

    while (i < len)
    {
        sum += subset[i];
        i++;
    }
    if (x == sum)
        return 1;
    return 0;
}

void print_sol(int *subset, int len)
{
    int i = 0;

    if (len == 0)
        return;
    //printf("Length: %d\n", len);
    //printf("Result:");
    while (i < len)
    {
        printf(" %d", subset[i]);
        i++;
    }
    printf("\n");
}

void gen_powerset(int x, int *set, int set_size)
{
    int counter = 0;
    int i = 0;
    int j = 0;
    int *subset = malloc(set_size * sizeof(int));
    unsigned int powerset_size = 1;

    while (i < set_size)
    {
        powerset_size *= 2;
        i++;
    }
    printf("powerset_size %d \n" , powerset_size);
    while (counter < powerset_size)
    {
        i = 0;
        j = 0;
        while (j < set_size)
        {
            if (counter & (1 << j))
            {
                subset[i] = set[j];
                i++;
            }
            j++;
        }
        if (sum_check(x, subset, i))
            print_sol(subset, i);
        counter++;
    }
    free(subset);
}

int main(int argc, char **av)
{
    if (argc < 3)
    {
        printf("Usage: %s <target_sum> <set_elements...>\n", av[0]);
        return 1;
    }
    // The first argument is the target sum (x)
    int x = atoi(av[1]);
    int set_size = argc - 2;  // Number of elements is total arguments minus target sum
    int *set = malloc(set_size * sizeof(int));

    int i = 0;
    while (i < set_size)
    {
        set[i] = atoi(av[i + 2]);
        i++;
    }

    // Generate powerset and check for subsets with sum equal to x
    gen_powerset(x, set, set_size);

    // Free the dynamically allocated memory for the set
    free(set);

    return 0;
}
