/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:06:33 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/05 13:49:28 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    count(void *global_v)
{
    t_global    *global;
    int         i;
    int         j;

    i = 0;
    global = (t_global *)global_v;
    while (i < global->eat_count)
    {
        j = 0;
        while (j < global->n_philos)
            pthread_mutex_lock(&global->philos[j++].mutex_eat);
        i++;
    }
    pthread_mutex_lock(&global->mutex_print);
    printf("PHILOSOPHERS HAVE SURVIVED 💅 💅 💅 !!!\n");
    pthread_mutex_unlock(&global->mutex_dead);
}

void    *dead(void *philo_void)
{
    t_philos    *philos;
     u_int64_t   time;
    
    philos = (t_philos *)philo_void;
    while (1)
    {
        pthread_mutex_lock(&philos->mutex);
         time = gettime();
      
        if (philos->eating == 0 && gettime() > philos->limit)
        {
            print_ms(philos, "has died 💀\n", 1);
            pthread_mutex_unlock(&philos->mutex);
            pthread_mutex_unlock(&philos->global->mutex_dead);
        }
        pthread_mutex_unlock(&philos->mutex);
        usleep(1000);
    }
}

void    life(t_philos *philos)
{
    pthread_mutex_lock(&philos->global->mutex_forks[philos->fork_l]);
    print_ms(philos, "has taken one fork 🍴 \n", 0);
    pthread_mutex_lock(&philos->global->mutex_forks[philos->fork_r]);
    print_ms(philos, "has taken another fork 🍴 \n", 0);
    pthread_mutex_lock(&philos->mutex);
    philos->eating = 1;
    philos->last_eat = gettime();
    philos->limit = philos->last_eat + philos->global->t_die;
    print_ms(philos, "is eating 🍝\n", 0);
    usleep(philos->global->t_eat * 1000);
    philos->eat_count_philo++;
    philos->eating = 0;
    pthread_mutex_unlock(&philos->mutex);
    pthread_mutex_unlock(&philos->mutex_eat);
    print_ms(philos, "is sleeping 😴\n", 0);
    pthread_mutex_unlock(&philos->global->mutex_forks[philos->fork_l]);
    pthread_mutex_unlock(&philos->global->mutex_forks[philos->fork_r]);
    usleep(philos->global->t_sleep * 1000);
    print_ms(philos, "is thinking 🤔 \n", 0);   
}

void    *routin(void *philo_void)
{
    t_philos    *philos;
    pthread_t   thread;
    
    philos = (t_philos*)philo_void;
    philos->last_eat = gettime();
    philos->limit = philos->last_eat + philos->global->t_die;
    pthread_create(&thread, NULL, &dead, philo_void);
    pthread_detach(thread);
    while (1)
        life(philos);
        
}


int start_threads(t_global *global)
{
    int         i;
    pthread_t   thread;
    void        *philo_void;
    
    i = 0;
    global->start = gettime();
    if (global->eat_count > 0 )
	{
		pthread_create(&thread, NULL, (void *)&count, (void*)global);
		pthread_detach(thread);
	}
    while (i < global->n_philos)
    {
        philo_void = (void *)(&global->philos[i]);
        pthread_create(&thread, NULL, &routin, philo_void);
        pthread_detach(thread);
        usleep(100);
        i++;
    }
    return (0);
}