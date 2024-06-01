/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:12:52 by ozini             #+#    #+#             */
/*   Updated: 2024/06/01 13:07:11 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;
int lock = 0;
pthread_mutex_t mutex;

void*	ultimate_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;

	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->left_fork);
	//eating
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	//sleeping
	//thinking

	
}


void*   routine_w_struct(void *arg)
{
    t_prompt_data    *prompt;

    prompt = (t_prompt_data *)arg;
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
void print_prompt_values(t_prompt_data *prompt)
{
    printf("El número de hilos es %d\n", prompt->philo_nbr);
    printf("El tiempo de muerte es %d\n", prompt->time_to_die);
    printf("El tiempo para comer es %d\n", prompt->time_to_eat);
    printf("El tiempo para dormir es %d\n", prompt->time_to_sleep);
    if (prompt->nbr_of_meals)
        printf("El número máximo de comidas es %d\n", prompt->nbr_of_meals);    
}

int main(int argc, char **argv)
{
    t_meal			*meal;
    pthread_t       *th;
    pthread_mutex_t *mutexes;
    int             i;

    meal = NULL;
    th = NULL;
    i = 0;
    if(argc == 5 || argc == 6)
    {
		//Comprobar que los datos metidos son todos numéricos.
		//Inicializar los datos (campo 'data' de 'meal')
        meal = initialize_meal(argc, argv);
        if(meal == NULL)
        {
            printf("Failed to allocate memory\n");
            return 1;
        }
        pthread_mutex_init(&mutex, NULL);
        while(i < meal->data->philo_nbr)
        {
            pthread_create(&th[i], NULL, &routine_w_struct,(void *)meal);
            i++;
        }
        i = 0;
        while(i < meal->data->philo_nbr)
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