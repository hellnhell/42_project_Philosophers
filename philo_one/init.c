/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:32:52 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/05 12:43:27 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int     init_philos(t_global *global)
{
    int i;

    i = 0;
    //puede q asegure los mutex
    pthread_mutex_init(&global->mutex_print, NULL);
    pthread_mutex_init(&global->mutex_dead, NULL);
    pthread_mutex_lock(&global->mutex_dead);
    global->mutex_forks = (pthread_mutex_t *)malloc(sizeof(*(global->mutex_forks)) * global->n_philos);
    if(!global->mutex_forks)
        return(printf("Error : Mutex_forks malloc\n"));
    while (i < global->n_philos)
    {
        global->philos[i].position = i;
        global->philos[i].fork_l = i;
        global->philos[i].fork_r = (i + 1) % global->n_philos; 
        global->philos[i].global = global;
        global->philos[i].eating = 0;
        global->philos[i].eat_count_philo = 0;
        pthread_mutex_init(&global->philos[i].mutex, NULL);
        pthread_mutex_init(&global->philos[i].mutex_eat, NULL);
        pthread_mutex_lock(&global->philos[i].mutex_eat);
        pthread_mutex_init(&global->mutex_forks[i], NULL);
        i++;
    }
    return (0);   
}