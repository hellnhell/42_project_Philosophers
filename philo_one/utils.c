/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:03:38 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/06 13:25:26 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

u_int64_t    gettime(void)
{
    static struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int         ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

int         ft_atoi(const char *s)
{
    int i;
    int nb;

    i = 0;
    nb = 0;
    while (s[i] >= '0' && s[i] <= '9')
    {
        nb = (nb * 10) + (s[i] - '0');
        i++;
    }
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
    {
        while (i < global->n_philo)
        {
            pthread_mutex_destroy(&global->philo[i].mutex);
            pthread_mutex_destroy(&global->philo[i].mutex_eat);
            i++;
        }
        free(global->philo);
    }
    pthread_mutex_destroy(&global->mutex_print);
    pthread_mutex_destroy(&global->mutex_dead);
    return (1);
} 
