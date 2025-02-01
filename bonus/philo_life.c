#include "../philo_bonus.h"

void philo_life(t_philo_b *philo) {
  while (philo->table->simulating) {
    int i;

    sem_wait(philo->table->semaphore);
    i = 0;
    while (i < philo->table->group_size){
      if (philo->table->eating_indexes[i] == philo->id) {
        philo->can_eat = true;
        break;
      }
      i++;
    }
    if (philo->can_eat)
    {
      print_message_b(philo, "is eating\n");
      philo->last_eat = get_timestamp_b(philo->table);
      usleep(philo->table->time_to_eat * 1000);
      philo->eat_count++;
      if (philo->eat_count == philo->table->must_eat_count)
        philo->full = true;
    }
    sem_post(philo->table->semaphore);
    print_message_b(philo, "is sleeping\n");
    usleep(philo->table->time_to_sleep * 1000);
    print_message_b(philo, "is thinking\n");
  }
}
