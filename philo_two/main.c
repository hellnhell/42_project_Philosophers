/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:08:03 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/12 10:41:10 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

static int    gerror_args(int argc, char **argv)
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

static void    get_args(t_global *global, char **argv, int argc)
{
    global->n_philo = ft_atoi(argv[1]);
    global->t_die = ft_atoi(argv[2]);
    global->t_eat = ft_atoi(argv[3]);
    global->t_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        global->eat_count = ft_atoi(argv[5]);
    else
        global->eat_count = 0;
    global->sem_fork = "sem_fork";
    global->sem_dead = "sem_dead";
    global->sem_print = "sem_print";
}

int     main(int argc, char **argv)
{
    t_global    *global;

    if(!gerror_args(argc, argv))
        return (-1);
    global = malloc(sizeof(t_global));
    if (!global)
        return (0);
    get_args(global, argv, argc);
    if ((global->n_philo < 2 || global->n_philo > 200 || global->t_die < 60
    || global->t_eat < 60 || global->t_sleep < 60 || global->eat_count < 0))
        return (printf("Error: Bad arguments\n"));
    init_philos(global);
    start_threads(global);
    sem_wait(global->mutex_dead);
    return (0);
}
