#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SEM_FORK_NAME "/fork_sem"

typedef struct s_philo
{
	int		id;
	sem_t	*left_fork;
	sem_t	*right_fork;
	sem_t	*sem_print;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
}			t_philo;

// Function to print philosopher's actions safely
void	print_message(t_philo *philo, const char *message)
{
	sem_wait(philo->sem_print);
	printf("Philosopher %d %s\n", philo->id, message);
	sem_post(philo->sem_print);
}

// Philosopher's life cycle
void	philo_life(t_philo *philo)
{
	while (1)
	{
		print_message(philo, "is thinking");
		usleep(philo->time_to_sleep * 1000);
		sem_wait(philo->left_fork);
		print_message(philo, "has taken left fork");
		sem_wait(philo->right_fork);
		print_message(philo, "has taken right fork");
		print_message(philo, "is eating");
		usleep(philo->time_to_eat * 1000);
		sem_post(philo->right_fork);
		sem_post(philo->left_fork);
		print_message(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
	}
}

// Create philosopher process
void	create_philosophers(int n, int time_to_die, int time_to_eat,
		int time_to_sleep)
{
	pid_t	pid;
	int		i;
	t_philo	philo;
	sem_t	*forks;
	sem_t	*sem_print;

	forks = sem_open(SEM_FORK_NAME, O_CREAT, 0644, n);
	// Semaphore for forks
	sem_print = sem_open("/sem_print", O_CREAT, 0644, 1);
	// Semaphore for safe printing
	if (forks == SEM_FAILED || sem_print == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(1);
	}
	for (i = 0; i < n; i++)
	{
		pid = fork();
		if (pid == 0)
		{
			// Child process: Philosopher's life
			philo.id = i + 1;
			philo.left_fork = forks;
			philo.right_fork = forks;
			philo.sem_print = sem_print;
			philo.time_to_die = time_to_die;
			philo.time_to_eat = time_to_eat;
			philo.time_to_sleep = time_to_sleep;
			philo_life(&philo);
			exit(0);
		}
	}
	// Parent process waits for all philosophers to finish
	for (i = 0; i < n; i++)
	{
		wait(NULL);
	}
	sem_close(forks);
	sem_close(sem_print);
	sem_unlink(SEM_FORK_NAME);
	sem_unlink("/sem_print");
}

int	main(int argc, char **argv)
{
	int	num_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;

	if (argc < 5)
	{
		printf("Usage:
				% s<num_of_philosophers><time_to_die><time_to_eat><time_to_sleep>\n ",
				argv[0]);
		return (1);
	}
	num_of_philosophers = atoi(argv[1]);
	time_to_die = atoi(argv[2]);
	time_to_eat = atoi(argv[3]);
	time_to_sleep = atoi(argv[4]);
	create_philosophers(num_of_philosophers, time_to_die, time_to_eat,
		time_to_sleep);
	return (0);
}
