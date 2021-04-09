/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:06:33 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/09 11:53:21 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    count(void *global_v)
{
    t_global    *global;

    global = (t_global *)global_v;
    while (1)
    {
        if (global->eat_count_philo > global->eat_count * global->n_philo)
        {
            print_ms(global->philo, "PHILOSOPHERS HAVE SURVIVED 💅 💅 💅 !!!\n", 1);
            pthread_mutex_unlock(&global->mutex_dead);
        } 
    }
}

void    *dead(void *philo_void)
{
    t_philo     *philo;
     uint64_t   time;
    
    philo = (t_philo *)philo_void;
    while (1)
    {
        time = gettime();
        if (philo->eating == 0 && time > philo->limit)
        {
            print_ms(philo, "has died 💀\n", 1);
            pthread_mutex_unlock(&philo->global->mutex_dead);
        }
        usleep(1000);
    }
}

void    life(t_philo *philo)
{
    pthread_mutex_lock(&philo->global->mutex_forks[philo->fork_l]);
    print_ms(philo, "has taken one fork 🍴 \n", 0);
    pthread_mutex_lock(&philo->global->mutex_forks[philo->fork_r]);
    print_ms(philo, "has taken another fork 🍴 \n", 0);
    philo->eating = 1;
    philo->last_eat = gettime();
    philo->limit = philo->last_eat + philo->global->t_die;
    print_ms(philo, "is eating 🍝\n", 0);
    philo->global->eat_count_philo++;
    usleep(philo->global->t_eat * 1000);
    pthread_mutex_unlock(&philo->global->mutex_forks[philo->fork_l]);
    pthread_mutex_unlock(&philo->global->mutex_forks[philo->fork_r]);
    print_ms(philo, "is sleeping 😴\n", 0);
    usleep(philo->global->t_sleep * 1000);
    print_ms(philo, "is thinking 🤔 \n", 0);
}

void    *routin(void *philo_void)
{
    t_philo     *philo;
    pthread_t   thread;
    
    philo = (t_philo *)philo_void;
    philo->last_eat = gettime();
    philo->limit = philo->last_eat + philo->global->t_die;
    pthread_create(&thread, NULL, &dead, philo_void);
    pthread_detach(thread); //reclaimed variables when thrad is finished
    while (1)
        life(philo);
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
    while (i < global->n_philo)
    {
        philo_void = (void *)(&global->philo[i]);
        pthread_create(&thread, NULL, &routin, philo_void);
        pthread_detach(thread);
        usleep(100);
        i++;
    }
    return (0);
}
