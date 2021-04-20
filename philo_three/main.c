/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:08:03 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/20 14:12:24 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	gerror_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6 )
	{
		printf("Error: Bad number of arguments\n");
		return (0);
	}
	if ((ft_atoi(argv[1]) <= 1 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
			|| ft_atoi(argv[4]) <= 0))
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
	{
		printf("Error: No meals\n");
		return (0);
	}
	return (1);
}

static void	get_args(t_glob *glob, char **argv, int argc)
{
	glob->n_philo = ft_atoi(argv[1]);
	glob->t_die = ft_atoi(argv[2]);
	glob->t_eat = ft_atoi(argv[3]);
	glob->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		glob->eat_count = ft_atoi(argv[5]);
	else
		glob->eat_count = 0;
	glob->ea = 0;
	glob->sem_fork = "sem_fork";
	glob->sem_dead = "sem_dead";
	glob->sem_print = "sem_print";
	glob->sem_count = "sem_count";
}

int	main(int argc, char **argv)
{
	t_glob	*glob;

	if (!gerror_args(argc, argv))
		return (-1);
	glob = malloc(sizeof(t_glob));
	if (!glob)
		return (0);
	get_args(glob, argv, argc);
	if ((glob->n_philo < 2 || glob->n_philo > 200 || glob->t_die < 60
			|| glob->t_eat < 60 || glob->t_sleep < 60 || glob->eat_count < 0))
		return (printf("Error: Bad arguments\n"));
	init_philos(glob);
	start_threads(glob);
	sem_wait(glob->mutex_dead);
	return (0);
}
