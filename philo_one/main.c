/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 19:02:43 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/05 12:19:58 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int     main(int argc, char **argv)
{
    t_global    global;
    
    if (argc < 5 || argc > 6 )
       return (printf("Error: Bad arguments\n"));
    global.n_philos = ft_atoi(argv[1]);
    global.t_die = ft_atoi(argv[2]);
    global.t_eat = ft_atoi(argv[3]);
    global.t_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        global.eat_count = ft_atoi(argv[5]);
    if ((global.n_philos < 2 || global.n_philos > 200 || global.t_die < 60
    || global.t_eat < 60 || global.t_sleep < 60))
        return (printf("Error: Bad arguments\n"));
    global.philos = (t_philos *)malloc(sizeof(*(global.philos)) * global.n_philos);
    if (!global.philos)
       return (printf("Error: Global malloc\n"));
    init_philos(&global);
    start_threads(&global);
    pthread_mutex_lock(&global.mutex_dead);
    free_global(&global);
    return (0);
}