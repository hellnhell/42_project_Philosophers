/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:08:48 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/20 14:11:12 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	count(void *global_v)
{
	t_glob	*glob;

	glob = (t_glob *)global_v;
	while (1)
	{
		sem_wait(glob->philo->mtx);
		if (glob->eat_count_philo > glob->eat_count * glob->n_philo)
		{
			print_ms(glob->philo, "PHILOSOPHERS HAVE SURVIVED 💅 💅 💅 !!!\n", 1);
			sem_post(glob->philo->mtx);
			sem_post(glob->mtx_dead);
			printf("eat count = %d\n", glob->eat_count_philo - 1);
		}
		sem_post(glob->philo->mtx);
	}
}

void	*dead(void	*philo_void)
{
	t_philo		*philo;
	u_int64_t	time;

	philo = (t_philo *)philo_void;
	while (1)
	{
		sem_wait(philo->mtx);
		time = gettime();
		if (!philo->eating && time > philo->limit)
		{
			print_ms(philo, "has died 💀\n", 1);
			sem_post(philo->mtx);
			sem_post(philo->glob->mtx_dead);
		}
		sem_post(philo->mtx);
		usleep(1000);
	}
}

void	life(t_philo *philo)
{
	sem_wait(philo->glob->mtx_forks);
	print_ms(philo, "has taken one fork 🍴 \n", 0);
	sem_wait(philo->glob->mtx_forks);
	print_ms(philo, "has taken another fork 🍴 \n", 0);
	sem_wait(philo->mtx);
	sem_wait(philo->mtx_eat);
	philo->eating = 1;
	philo->last_eat = gettime();
	philo->limit = philo->last_eat + philo->glob->t_die;
	print_ms(philo, "is eating 🍝\n", 0);
	philo->glob->eat_count_philo++;
	usleep(philo->glob->t_eat * 850);
	philo->eating = 0;
	sem_post(philo->mtx_eat);
	sem_post(philo->mtx);
	print_ms(philo, "is sleeping 😴\n", 0);
	sem_post(philo->glob->mtx_forks);
	sem_post(philo->glob->mtx_forks);
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
	pthread_create(&thread, NULL, &dead, philo_void);
	pthread_detach(thread);
	while (1)
		life(philo);
}

int	start_threads(t_glob *glob)
{
	int			i;
	pthread_t	thread;
	void		*philo_void;

	i = 0;
	if (glob->eat_count > 0)
	{
		pthread_create(&thread, NULL, (void *)&count, (void *)glob);
		pthread_detach(thread);
	}
	glob->start = gettime();
	while (i < glob->n_philo)
	{
		philo_void = (void *)(&glob->philo[i]);
		pthread_create(&thread, NULL, &routine, philo_void);
		pthread_detach(thread);
		usleep(100);
		i++;
	}
	return (0);
}
