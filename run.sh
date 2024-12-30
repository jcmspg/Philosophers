#bash script
# run the program
# Usage: bash run.sh


# Run the program with valgrind for memory check and leak check
# valgrind --leak-check=full --track-origins=yes ./bin/program

# Run the program 
# change the number of philosophers and the time to die according to the arguments
#
# ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
#
# Example:
# ./philo 4 410 200 200 200
# ./philo 5 800 200 200 200
# ./philo 6 800 200 200 200
#

# Run this script but use arguments read from the terminal
# example: bash run.sh 4 410 200 200 200
valgrind --leak-check=full --track-origins=yes ./philo $1 $2 $3 $4 $5


