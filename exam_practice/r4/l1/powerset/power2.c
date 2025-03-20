#include "powerset.h"

void print_sol(int *subset, int len)
{
    int i = 0;
    if (len == 0) return;

    while (i < len)
    {
        printf(" %d", subset[i]);
        i++;
    }
    printf("\n");
}

void find_subsets(int *set, int *subset, int set_size, int index, int x, int subset_size)
{
    // If we've checked all elements in the set
    if (index == set_size)
    {
        // Check the sum of the current subset
        int sum = 0;
        int i = 0;
        while (i < subset_size)
        {
            sum += subset[i];
            i++;
        }

        if (sum == x) {
            print_sol(subset, subset_size);
        }
        return;
    }

    // Exclude the current element
    find_subsets(set, subset, set_size, index + 1, x, subset_size);

    // Include the current element
    subset[subset_size] = set[index];
    find_subsets(set, subset, set_size, index + 1, x, subset_size + 1);
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

    // Fill the set array with values from the command line arguments
    int i = 0;
    while (i < set_size)
    {
        set[i] = atoi(av[i + 2]);
        i++;
    }

    int *subset = malloc(set_size * sizeof(int)); // Temporary array for subsets

    // Generate subsets and check for subsets with sum equal to x
    find_subsets(set, subset, set_size, 0, x, 0);

    free(set);
    free(subset);

    return 0;
}
