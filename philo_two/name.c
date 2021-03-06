/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:51:17 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/20 13:45:35 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*name(char *s1, char *dst, int num_philos)
{
	int		i;
	int		j;
	char	s3[250];

	j = 0;
	while (s1[j] != '\0')
	{
		dst[j] = s1[j];
		j++;
	}
	i = 0;
	while (num_philos > 0)
	{
		s3[i++] = (num_philos % 10) + '0';
		num_philos = num_philos / 10;
	}
	while (i > 0)
	{
		dst[j] = s3[--i];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
