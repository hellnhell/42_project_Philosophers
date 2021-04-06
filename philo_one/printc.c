/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:14:36 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/06 13:34:55 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    ft_putchar(char c)
{
  write(1 , &c, 1);
}

void    ft_putnbr(int nb)
{
	if ((nb / 10) > 0)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + 48);
}

int print_ms(t_philo *philo, char *str, int n)
{
    u_int64_t   time;

    pthread_mutex_lock(&philo->global->mutex_print);
    time = gettime();
    ft_putnbr(time - philo->global->start);
    write(1, "\t", 1);
    ft_putnbr(philo->position + 1);
    write(1, "\t", 1);
    write(1, str, ft_strlen(str));
    if (n == 1)
        return (0);    
    pthread_mutex_unlock(&philo->global->mutex_print);
    return (0);
}
