/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:36:24 by emartin-          #+#    #+#             */
/*   Updated: 2021/04/20 14:26:35 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*count(void *philo_void)
{
	t_glob	*glob;
	int		i;

	glob = (t_glob *)philo_void;
	i = -1;
	while (++i < glob->n_philo)
		sem_wait(glob->mutex_count);
	print_ms(glob->philo, "PHILOSOPHERS HAVE SURVIVED 💅 💅 💅 !!!\n", 1);
	sem_post(glob->philo->mutex);
	sem_post(glob->mutex_dead);
	return (NULL);
}

void	*dead(void	*philo_void)
{
	t_philo		*philo;
	u_int64_t	time;

	philo = (t_philo *)philo_void;
	while (1)
	{
		sem_wait(philo->mutex);
		time = gettime();
		if (!philo->eating && time > philo->limit)
		{
			print_ms(philo, "has died 💀\n", 1);
			sem_post(philo->mutex);
			sem_post(philo->glob->mutex_dead);
		}
		sem_post(philo->mutex);
		usleep(1000);
	}
}

void	life(t_philo *philo)
{
	sem_wait(philo->glob->mutex_forks);
	print_ms(philo, "has taken one fork 🍴 \n", 0);
	sem_wait(philo->glob->mutex_forks);
	print_ms(philo, "has taken another fork 🍴 \n", 0);
	sem_wait(philo->mutex);
	sem_wait(philo->mutex_eat);
	philo->eating = 1;
	philo->last_eat = gettime();
	philo->limit = philo->last_eat + philo->glob->t_die;
	if (philo->eat_count_philo == philo->glob->eat_count)
		sem_post(philo->glob->mutex_count);
	print_ms(philo, "is eating 🍝\n", 0);
	philo->eat_count_philo++;
	usleep(philo->glob->t_eat * 850);
	philo->eating = 0;
	sem_post(philo->mutex_eat);
	sem_post(philo->mutex);
	print_ms(philo, "is sleeping 😴\n", 0);
	sem_post(philo->glob->mutex_forks);
	sem_post(philo->glob->mutex_forks);
	usleep(philo->glob->t_sleep * 850);
	print_ms(philo, "is thinking 🤔 \n", 0);
}

void	*routine(void *philo_void)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)philo_void;
	philo->last_eat = gettime();
	philo->limit = philo->last_eat + philo->glob->t_die;
	if (pthread_create(&thread, NULL, dead, philo_void) != 0)
		return ((void *)1);
	pthread_detach(thread);
	while (1)
		life(philo);
	return ((void *)0);
}

int	start_threads(t_glob *glob)
{
	int			i;
	pthread_t	thread;

	i = 0;
	if (glob->eat_count > 0)
	{
		pthread_create(&thread, NULL, count, (void *)glob);
		pthread_detach(thread);
	}
	glob->start = gettime();
	while (i < glob->n_philo)
	{
		glob->philo[i].pid = fork();
		if (glob->philo[i].pid < 0)
			return (0);
		if (glob->philo[i].pid == 0)
		{
			routine(&glob->philo[i]);
			exit (0);
		}
		usleep(100);
		i++;
	}
	return (0);
}
