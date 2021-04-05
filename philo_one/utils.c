/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:03:38 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/05 11:44:05 by emartin-         ###   ########.fr       */
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

char    *ft_strcpy(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s2[i] != '\0')
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
    return (s1);
}

int     free_global(t_global *global)
{
    int i;

    i = 0;
    if (global->mutex_forks)
    {
        while (i < global->n_philos)
            pthread_mutex_destroy(&global->mutex_forks[i++]);
        free(global->mutex_forks);
    }
    i = 0;
    if (global->philos)
    {
        while (i < global->n_philos)
        {
            pthread_mutex_destroy(&global->philos[i].mutex);
            pthread_mutex_destroy(&global->philos[i].mutex_eat);
            i++;
        }
        free(global->philos);
    }
    pthread_mutex_destroy(&global->mutex_print);
    pthread_mutex_destroy(&global->mutex_dead);
    return (1);
}