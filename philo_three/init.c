/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:30:43 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/20 14:05:33 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	unlink_gl_sem(t_glob *glob)
{
	sem_unlink(glob->sem_fork);
	sem_unlink(glob->sem_print);
	sem_unlink(glob->sem_dead);
	sem_unlink(glob->sem_count);
}

static int	gl_sem_init(t_glob *glob)
{
	glob->mutex_forks = sem_open(glob->sem_fork, O_CREAT, 0644, glob->n_philo);
	glob->mutex_dead = sem_open(glob->sem_dead, O_CREAT, 0644, 0);
	glob->mutex_print = sem_open(glob->sem_print, O_CREAT, 0644, 1);
	glob->mutex_count = sem_open(glob->sem_count, O_CREAT, 0644, 0);
	glob->philo = (t_philo *)malloc(sizeof(*(glob->philo)) * glob->n_philo);
	if (!glob->philo)
		return (printf("Error: Global malloc\n"));
	return (0);
}

int	init_philos(t_glob *glob)
{
	char	sem_name[200];
	int		i;

	i = 0;
	unlink_gl_sem(glob);
	gl_sem_init(glob);
	while (i < glob->n_philo)
	{
		glob->philo[i].position = i;
		glob->philo[i].fork_l = (i + 1) % glob->n_philo;
		glob->philo[i].fork_r = i;
		glob->philo[i].glob = glob;
		glob->philo[i].eating = 0;
		glob->philo[i].eat_count_philo = 1;
		name("sem_philo", sem_name, i);
		sem_unlink(sem_name);
		glob->philo[i].mutex = sem_open(sem_name, O_CREAT, 0644, 1);
		name("sem_philoeat", sem_name, i);
		sem_unlink(sem_name);
		glob->philo[i].mutex_eat = sem_open(sem_name, O_CREAT, 0644, 1);
		i++;
	}
	return (0);
}
