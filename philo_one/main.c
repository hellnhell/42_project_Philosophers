/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:02:43 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/20 12:11:27 by emartin-         ###   ########.fr       */
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

static void	get_args(t_global *global, int argc, char **argv)
{
	global->n_philo = ft_atoi(argv[1]);
	global->t_die = ft_atoi(argv[2]);
	global->t_eat = ft_atoi(argv[3]);
	global->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		global->eat_count = ft_atoi(argv[5]);
	else
		global->eat_count = 0;
}

int	main(int argc, char **argv)
{
	t_global	*global;

	if (!gerror_args(argc, argv))
		return (-1);
	global = malloc(sizeof(t_global));
	if (!global)
		return (0);
	get_args(global, argc, argv);
	if ((global->n_philo < 2 || global->n_philo > 200 || global->t_die < 60
			|| global->t_eat < 60 || global->t_sleep < 60
			|| global->eat_count < 0))
		return (printf("Error: Bad arguments\n"));
	if (!init_philos(global))
		return (printf("Error: Mem allocation\n"));
	if (!start_threads(global))
		return (printf("Unexpected Error\n"));
	pthread_mutex_lock(&global->mutex_dead);
	return (0);
}
