/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:12:52 by ozini             #+#    #+#             */
/*   Updated: 2024/05/28 17:49:56 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

int mails = 0;
int lock = 0;
pthread_mutex_t mutex;

typedef struct prompt_data_s
{
    int philo_nbr;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_of_meals;
    long    initial_time;
}   prompt_data_t;

long    get_absolute_microseconds()
{
    struct timeval tv;
    long    microseconds;
    
    gettimeofday(&tv, NULL);
    microseconds = tv.tv_sec * 1000000 + tv.tv_usec;
    return (microseconds);
    
}
long    get_relative_microseconds(long initial_time)
{
    long    current_microseconds;

    current_microseconds = get_absolute_microseconds();
    return(current_microseconds - initial_time);
}
void*   routine_w_struct(void *arg)
{
    prompt_data_t    *prompt;

    prompt = (prompt_data_t *)arg;
    pthread_mutex_lock(&mutex);
    //eating.
    usleep(prompt->time_to_eat);
    pthread_mutex_unlock(&mutex);
    printf("El tiempo transcurrido comiendo es %ld\n", get_relative_microseconds(prompt->initial_time));
    //sleeping
    usleep(200);
    printf("El tiempo transcurrido durmiendo es %ld\n", get_relative_microseconds(prompt->initial_time));
    return (NULL);  
}

void*	full_routine(void *arg)
{
	long	initial_time;

	initial_time = *(long *)arg;
	pthread_mutex_lock(&mutex);
	//eating.
	usleep(800);
	pthread_mutex_unlock(&mutex);
	printf("El tiempo transcurrido comiendo es %ld\n", get_relative_microseconds(initial_time));
	//sleeping
	usleep(200);
	printf("El tiempo transcurrido durmiendo es %ld\n", get_relative_microseconds(initial_time));
	return (NULL);  
}
void*   routine()
{
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        // read mails
        // increment
        // write to mails
        // gcc -S race_condition.c
    }
    return (NULL);
}
int ft_atoi(char *str)
{
    long number;
    int sign;

    number = 0;
    sign = 0;
    while(*str >= 9 && *str <= 13)
        str++;
    if(*str == '-' || *str == '+')
    {
        if(*str == '-')
            sign = 1;
        str++;
    }
    while(*str >= '0' && *str<= '9')
    {
        number = number * 10 + (*str - '0');
        str++;
    }
    if(sign)
        return (-number);
    else
        return (number);
}

prompt_data_t *init_prompt(int argc, char **argv)
{
    prompt_data_t   *prompt;
    int             i;
    
    i = 1;
    //Aquí tendría que meter una función que comprobase que
    //todos los valores son numéricos. Si alguna de ellos falla
    //devuelvo NULL.
    prompt = malloc(sizeof(prompt_data_t));
    if(prompt == NULL)
    {
        //Aqui pongo un fd_putstr con el fd = 2
        return(NULL);
    }
    while(i < argc)
    {
        if(i == 1)
            prompt->philo_nbr = ft_atoi(argv[1]);
        if(i == 2)
            prompt->time_to_die = ft_atoi(argv[2]);
        if(i == 3)
            prompt->time_to_eat = ft_atoi(argv[3]);
        if(i == 4)
            prompt->time_to_sleep = ft_atoi(argv[4]);
        i++;
    }
	prompt->initial_time = get_absolute_microseconds();
    if(i == 6)
    	prompt->nbr_of_meals = ft_atoi(argv[5]);
    else
    	prompt->nbr_of_meals = 0;
    return (prompt);
    
}

void print_prompt_values(prompt_data_t *prompt)
{
    printf("El número de hilos es %d\n", prompt->philo_nbr);
    printf("El tiempo de muerte es %d\n", prompt->time_to_die);
    printf("El tiempo para comer es %d\n", prompt->time_to_eat);
    printf("El tiempo para dormir es %d\n", prompt->time_to_sleep);
    if (prompt->nbr_of_meals)
        printf("El número máximo de comidas es %d\n", prompt->nbr_of_meals);    
}

pthread_t    *initiliaze_philosophers(int philo_nbr)
{
    pthread_t   *th;
    int         i;

    i = 0;
    th = malloc(philo_nbr * sizeof(pthread_t));
    if(th==NULL)
        return (NULL);
    return (th);
}
int main(int argc, char **argv)
{
    prompt_data_t   *prompt;
    pthread_t       *th;
    int             i;

    prompt = NULL;
    //initial_time = NULL;
    th = NULL;
    i = 0;
    if(argc == 5 || argc == 6)
    {
        printf("Correct number of arguments\n");
        prompt = init_prompt(argc, argv);
        if(prompt == NULL)
        {
            printf("Failed to allocate memory\n");
            return 1;
        }
/*         print_prompt_values(prompt);
        usleep(prompt->time_to_die);
        printf("Time elapsed time_to_die: %ld\n", get_relative_microseconds(prompt->initial_time));
        usleep(prompt->time_to_eat);
        printf("Time elapsed time_to_eat: %ld\n", get_relative_microseconds(prompt->initial_time));
        usleep(prompt->time_to_sleep);
        printf("Time elapsed time_to_sleep: %ld\n", get_relative_microseconds(prompt->initial_time)); */
        th = initiliaze_philosophers(prompt->philo_nbr);
        pthread_mutex_init(&mutex, NULL);
        while(i < prompt->philo_nbr)
        {
            //pthread_create(&th[i], NULL, &routine, NULL);
            //pthread_create(&th[i], NULL, &full_routine,(void *)&initial_time);
            pthread_create(&th[i], NULL, &routine_w_struct,(void *)prompt);
            i++;
        }
        i = 0;
        while(i < prompt->philo_nbr)
        {
            pthread_join(th[i], NULL);
            i++;
        }
        free(th);
        pthread_mutex_destroy(&mutex);
        //printf("The number of mails is: %d\n", mails);
    }
   else
        printf("Incorrect number of arguments\n");
}