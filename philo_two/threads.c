/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hellnhell <hellnhell@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:08:48 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/05 21:00:59 by hellnhell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    dead(void  *philo_void)
{
    t_philos    *philos;
    u_int64_t   time;
    
    philos = (t_philos *)philo_void;
    while (1)
    {
        sem_wait(philos->mutex);
        time = gettime();
        if (philos->eating == 0 && time > philos->limit)
        {
            print_ms(philos, "has died 💀\n", 1);
            sem_post(philos->mutex);
            sem_post(philos->global->mutex_dead);
        }
        sem_post(philos->mutex);  
    }
}

void    life(t_philos *philos)
{
    sem_wait(philos->global->mutex_forks);
    print_ms(philos, "has taken one fork 🍴 \n", 0);
    sem_wait(philos->global->mutex_forks);
    print_ms(philos, "has taken another fork 🍴 \n", 0);
    sem_wait(philos->mutex);
    sem_wait(philos->mutex_eat);
    philos->eating = 1;
    philos->last_eat = gettime();
    philos->limit = philos->last_eat + philos->global->t_die;
    print_ms(philos, "is eating 🍝\n", 0);
    usleep(philos->global->t_eat * 850);
    philos->eating = 0;
    sem_post(philos->mutex_eat);
    sem_post(philos->mutex);
    print_ms(philos, "is sleeping 😴\n", 0);
    sem_post(philos->global->mutex_forks);
    sem_post(philos->global->mutex_forks);
    usleep(philos->global->t_sleep * 850);
    print_ms(philos, "is thinking 🤔 \n", 0);   
}

void    *routin(void *philo_void)
{
    pthread_t   thread;
    t_philos    *philos;
    
    philos = (t_philos *)philo_void;
    philos->last_eat = gettime();
    philos->limit = philos->last_eat + philos->global->t_die;
    pthread_create(&thread, NULL, (void *)&dead, philo_void);
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