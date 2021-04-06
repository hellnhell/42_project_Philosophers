/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:32:52 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/06 13:33:51 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int     init_philos(t_global *global)
{
    int i;

    i = 0;
    pthread_mutex_lock(&global->mutex_dead);
    global->mutex_forks = (pthread_mutex_t *)malloc
    (sizeof(*(global->mutex_forks))* global->n_philo);
    if (!global->mutex_forks)
        return (printf("Error : Mutex_forks malloc\n"));
    while (i < global->n_philo)
    {
        global->philo[i].position = i;
        global->philo[i].fork_l = i;
        global->philo[i].fork_r = (i + 1) % global->n_philo; 
        global->philo[i].global = global;
        global->philo[i].eating = 0;
        global->philo[i].eat_count_philo = 0;
        pthread_mutex_init(&global->philo[i].mutex, NULL);
        pthread_mutex_init(&global->philo[i].mutex_eat, NULL);
        pthread_mutex_lock(&global->philo[i].mutex_eat);
        pthread_mutex_init(&global->mutex_forks[i], NULL);
        i++;
    }
    return (0);   
}
