/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:32:52 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/09 14:11:00 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int     init_mutex(t_global *global)
{
    pthread_mutex_init(&global->mutex_print, NULL);
    pthread_mutex_init(&global->mutex_dead, NULL);
    pthread_mutex_lock(&global->mutex_dead);
    global->mutex_forks = (pthread_mutex_t *)malloc
    (sizeof(*(global->mutex_forks))* global->n_philo);
    if (!global->mutex_forks)
        return (0);
    return (1);
}

int     init_philos(t_global *global)
{
    int i;

    i = 0;
    global->philo = (t_philo *)malloc(sizeof(*(global->philo)) * global->n_philo);
    if (!global->philo)
        return (0);
    init_mutex(global);
    global->eat_count_philo = 1;
    while (i < global->n_philo)
    {
        global->philo[i].position = i;
        global->philo[i].fork_l = i;
        global->philo[i].fork_r = (i + 1) % global->n_philo; 
        global->philo[i].global = global;
        global->philo[i].eating = 0;
        pthread_mutex_init(&global->mutex_forks[i], NULL);
        i++;
    }
    return (0);   
}
