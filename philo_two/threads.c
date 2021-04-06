/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:08:48 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/06 13:28:48 by emartin-         ###   ########.fr       */
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
        while (j < global->n_philo)
            sem_wait(global->philo[j++].mutex_eat);
        i++;
    }
    sem_wait(global->mutex_print);
    printf("PHILOSOPHERS HAVE SURVIVED 💅 💅 💅 !!!\n");
    sem_post(global->mutex_dead);
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
    }
}

void    life(t_philo *philo)
{
    sem_wait(philo->global->mutex_forks);
    print_ms(philo, "has taken one fork 🍴 \n", 0);
    sem_wait(philo->global->mutex_forks);
    print_ms(philo, "has taken another fork 🍴 \n", 0);
    sem_wait(philo->mutex);
    philo->eating = 1;
    philo->last_eat = gettime();
    philo->limit = philo->last_eat + philo->global->t_die;
    print_ms(philo, "is eating 🍝\n", 0);
    usleep(philo->global->t_eat * 850);
    philo->eat_count_philo++;
    philo->eating = 0;
    sem_post(philo->mutex);
    sem_post(philo->mutex_eat);
    print_ms(philo, "is sleeping 😴\n", 0);
    sem_post(philo->global->mutex_forks);
    sem_post(philo->global->mutex_forks);
    usleep(philo->global->t_sleep * 850);
    print_ms(philo, "is thinking 🤔 \n", 0);   
}

void    *routin(void *philo_void)
{
    pthread_t   thread;
    t_philo    *philo;
    
    philo = (t_philo *)philo_void;
    philo->last_eat = gettime();
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