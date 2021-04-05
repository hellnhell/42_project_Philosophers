/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hellnhell <hellnhell@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:30:43 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/05 21:05:27 by hellnhell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_philos(t_global *global)
{
    char    sem_name[200];
    int i;

    i = 0;
    
    sem_unlink(global->sem_fork); //Destruye el sem
    sem_unlink(global->sem_dead);
    sem_unlink(global->sem_print);
    global->sem_fork = "sem_fork";
    global->sem_dead = "sem_dead";
    global->sem_print = "sem_print";
    global->mutex_forks = sem_open(global->sem_fork, O_CREAT, 0644, global->n_philos);
    global->mutex_dead = sem_open(global->sem_dead, O_CREAT, 0644, 0);
    global->mutex_print = sem_open(global->sem_print, O_CREAT, 0644, 1);
    while (i < global->n_philos)
    {
        global->philos[i].position = i;
        global->philos[i].eating = 0;
        global->philos[i].fork_l = (i + 1) % global->n_philos;
        global->philos[i].fork_r = i;
        global->philos[i].global = global;
        name("sem_philo", sem_name, i);
        sem_unlink(sem_name);
        global->philos[i].mutex = sem_open(sem_name, O_CREAT, 0644, 1);
        name("sem_philoeat", sem_name, i);
        sem_unlink(sem_name);
        global->philos[i].mutex_eat = sem_open(sem_name, O_CREAT, 0644, 1);
        i++;
    }
    return (0);
}