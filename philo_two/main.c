/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:08:03 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/08 13:26:41 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

void    get_args(t_global *global, char **argv)
{
    global->n_philo = ft_atoi(argv[1]);
    global->t_die = ft_atoi(argv[2]);
    global->t_eat = ft_atoi(argv[3]);
    global->t_sleep = ft_atoi(argv[4]);
    global->sem_fork = "sem_fork";
    global->sem_dead = "sem_dead";
    global->sem_print = "sem_print";
}

int     main(int argc, char **argv)
{
    t_global    global;

    if (argc < 5 || argc > 6 )
       return (printf("Error: Bad number of arguments\n"));
    get_args(&global, argv);
    if (argc == 6)
        global.eat_count = ft_atoi(argv[5]);//Gestión errors
    else
        global.eat_count = 0;
    if ((global.n_philo < 2 || global.n_philo > 200 || global.t_die < 60
    || global.t_eat < 60 || global.t_sleep < 60 || global.eat_count < 0))
        return (printf("Error: Bad arguments\n"));
    global.mutex_forks = NULL;
	global.philo = NULL;
    global.eat_count_philo = 1;
    global.philo = (t_philo *)malloc(sizeof(*(global.philo)) * global.n_philo);
    if (!global.philo)
       return (printf("Error: Global malloc\n"));
    init_philos(&global);
    start_threads(&global);
    sem_wait(global.mutex_dead);
    return (0);
}