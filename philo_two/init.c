/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:30:43 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/15 13:27:34 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void    unlink_gl_sem(t_global *global)
{
    sem_unlink(global->sem_fork); 
    sem_unlink(global->sem_dead);
    sem_unlink(global->sem_print);
}

static int gl_sem_init(t_global *global)
{
    global->mutex_forks = sem_open(global->sem_fork, O_CREAT, 0644, global->n_philo);
    global->mutex_dead = sem_open(global->sem_dead, O_CREAT, 0644, 0);
    global->mutex_print = sem_open(global->sem_print, O_CREAT, 0644, 1);
    global->mutex_forks = NULL;
	global->philo = NULL;
    global->eat_count_philo = 1;
    global->philo = (t_philo *)malloc(sizeof(*(global->philo)) * global->n_philo);
    if (!global->philo)
       return (printf("Error: Global malloc\n"));
    return (0);    
}


int init_philos(t_global *global)
{
    char    sem_name[200];
    int i;

    i = 0;
    unlink_gl_sem(global);
    gl_sem_init(global);
    while (i < global->n_philo)
    {
        global->philo[i].position = i;
        global->philo[i].fork_r = (i + 1) % global->n_philo;
        global->philo[i].fork_l = i;
        global->philo[i].global = global;
        global->philo[i].eating = 0;
        name("sem_philo", sem_name, i);
        sem_unlink(sem_name);
        global->philo[i].mutex = sem_open(sem_name, O_CREAT, 0644, 1);
        name("sem_philoeat", sem_name, i);
        sem_unlink(sem_name);
        global->philo[i].mutex_eat = sem_open(sem_name, O_CREAT, 0644, 1);
        i++;
    }
    return (0);
}
