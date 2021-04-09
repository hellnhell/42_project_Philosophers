/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:03:38 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/09 11:24:45 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t    gettime(void)
{
    static struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int         ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

int         ft_atoi(const char *str)
{
  	int		i;
	int		neg;
	int		nb;

	i = 0;
	neg = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg++;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (neg == 1)
		nb = nb * (-1);
	return (nb);
}

int     free_global(t_global *global)
{
    int i;

    i = 0;
    if (global->mutex_forks)
    {
        while (i < global->n_philo)
            pthread_mutex_destroy(&global->mutex_forks[i++]);
        free(global->mutex_forks);
    }
    i = 0;
    if (global->philo)
        free(global->philo);
    pthread_mutex_destroy(&global->mutex_print);
    pthread_mutex_destroy(&global->mutex_dead);
    return (1);
} 
