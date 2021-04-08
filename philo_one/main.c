/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:02:43 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/08 14:14:37 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    get_args(t_global *global, int argc, char **argv)
{
    global->n_philo = ft_atoi(argv[1]);
    global->t_die = ft_atoi(argv[2]);
    global->t_eat = ft_atoi(argv[3]);
    global->t_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        global->eat_count = ft_atoi(argv[5]);
}

int     main(int argc, char **argv)
{
    t_global    global;

    if (argc < 5 || argc > 6 )
        return (printf("Error: Bad number of arguments\n"));
    get_args(&global, argc, argv);
    if ((global.n_philo < 2 || global.n_philo > 200 || global.t_die < 60
    || global.t_eat < 60 || global.t_sleep < 60))
        return (printf("Error: Bad arguments\n"));
    global.philo = (t_philo *)malloc(sizeof(*(global.philo)) * global.n_philo);
    if (!global.philo)
        return (printf("Error: Global malloc\n"));
    pthread_mutex_init(&global.mutex_print, NULL);
    pthread_mutex_init(&global.mutex_dead, NULL);
    global.eat_count_philo = 1;
    init_philos(&global);
    start_threads(&global);
    pthread_mutex_lock(&global.mutex_dead);
    free_global(&global);
    return (0);
}