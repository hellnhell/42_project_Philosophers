/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:08:48 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/07 14:30:32 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    count(void *global_v)
{
    t_global    *global;

    global = (t_global *)global_v;
    while (1)
    {
        // printf("p----%d\n", global->eat_count_philo);
        // printf("c----%d\n", global->n_philo * global->eat_count);
        if (global->eat_count_philo >= global->n_philo * global->eat_count)
        {
            print_ms(global->philo, "PHILOSOPHERS HAVE SURVIVED 💅 💅 💅 !!!\n", 1);
            sem_post(global->mutex_dead);
        }
        usleep(1000); 
    }
}

void    dead(void  *philo_void)
{
    t_philo    *philo;
    u_int64_t   time;
    
    philo = (t_philo *)philo_void;
    while (1)
    {
        sem_wait(philo->mutex);
        time = gettime();
        if (philo->eating == 0 && time > philo->limit)
        {
            print_ms(philo, "has died 💀\n", 1);
            sem_post(philo->mutex);
            sem_post(philo->global->mutex_dead);
        }
        sem_post(philo->mutex);
        usleep(1000); 
    }
}

void    life(t_philo *philo)
{
    sem_wait(philo->global->mutex_forks);
    print_ms(philo, "has taken one fork 🍴 \n", 0);
    sem_wait(philo->global->mutex_forks);
    print_ms(philo, "has taken another fork 🍴 \n", 0);
    sem_wait(philo->mutex);
    sem_wait(philo->mutex_eat);
    philo->eating = 1;
    philo->last_eat = gettime();
    // printf("le1 : %llu\n", philo->last_eat);
    philo->limit = philo->last_eat + philo->global->t_die;
    print_ms(philo, "is eating 🍝\n", 0);
    usleep(philo->global->t_eat * 1000);
    philo->global->eat_count_philo++;
    philo->eating = 0;
    sem_post(philo->mutex);
    sem_post(philo->mutex_eat);
    print_ms(philo, "is sleeping 😴\n", 0);
    sem_post(philo->global->mutex_forks);
    sem_post(philo->global->mutex_forks);
    usleep(philo->global->t_sleep * 1000);
    print_ms(philo, "is thinking 🤔 \n", 0);
}

void    *routin(void *philo_void)
{
    pthread_t   thread;
    t_philo    *philo;
    
    philo = (t_philo *)philo_void;
    philo->last_eat = gettime();
    // printf("le2 : %llu\n", philo->last_eat);
    philo->limit = philo->last_eat + philo->global->t_die;
    pthread_create(&thread, NULL, (void *)&dead, philo_void);
    pthread_detach(thread);
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
    // printf("start : %llu\n", global->start);
    if (global->eat_count > 0)
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
