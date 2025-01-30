#include <stdio.h>
#include <stdlib.h>

void round_robin(int n_philos, int round, int *last_eaten)
{
    int eating_count = n_philos / 2;
    printf("Round %d:\n", round + 1);

    // Reset last_eaten status for this round
    for (int i = 0; i < n_philos; i++) {
        last_eaten[i] = 0; // Reset last eaten status
    }

    // Determine the start index for the eating group
    int start = (round * eating_count) % n_philos;

    // Find philosophers who will eat in this round
    for (int i = 0; i < eating_count; i++) {
        int idx = (start + i) % n_philos;
        printf("Philosopher %d is eating\n", idx + 1);
        last_eaten[idx] = 1; // Mark as having eaten
    }

    // Mark all others as waiting
    for (int i = 0; i < n_philos; i++) {
        if (last_eaten[i] == 0) {
            printf("Philosopher %d is waiting\n", i + 1);
        }
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    int n_philos;
    int nbr_of_rounds;

    if (argc != 3)
    {
        printf("Usage: ./round_robin n_philos nbr_of_rounds\n");
        return 1;
    }

    n_philos = atoi(argv[1]);
    nbr_of_rounds = atoi(argv[2]);

    int *last_eaten = (int*)malloc(n_philos * sizeof(int));

    // Simulate the rounds
    for (int i = 0; i < nbr_of_rounds; i++)
    {
        round_robin(n_philos, i, last_eaten);
    }

    free(last_eaten);
    return 0;
}

