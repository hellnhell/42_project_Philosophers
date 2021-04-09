/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:53:05 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/09 11:23:45 by emartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>


typedef struct s_philo
{
    int             position;
    int             eating;
    int             fork_l;
    int             fork_r;
    uint64_t       limit;
    uint64_t       last_eat;
    struct s_global *global;
}             t_philo;

typedef struct s_global
{
    int             n_philo;
    int             n_eats;
    int             eat_count_philo;
    int             eat_count;
    uint64_t       t_eat;
    uint64_t       t_sleep;
    uint64_t       t_die;
    uint64_t       start;
    t_philo        *philo;
    pthread_mutex_t *mutex_forks; 
    pthread_mutex_t mutex_print;
    pthread_mutex_t mutex_dead;
}              t_global;


int         ft_strlen(char *str);
void	    ft_putnbr(int nb);
int         ft_atoi(const char *str);
int         main(int argc, char **argv);
int         init_philos(t_global *global);
int         start_threads(t_global *global);
void        *routine(void *philo_void);
void        *dead(void *philo_void);
void        life(t_philo *philo);
void        count(void *global_v);
uint64_t   gettime(void);
int         print_ms(t_philo *philo, char *str, int n);
int         free_global(t_global *global);

#endif