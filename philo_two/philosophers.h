/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartin- <emartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:53:05 by hellnhell         #+#    #+#             */
/*   Updated: 2021/04/08 13:40:40 by emartin-         ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_philo
{
    int             position;
    int             eating;
    int             fork_l;
    int             fork_r;
    u_int64_t       limit;
    u_int64_t       last_eat;
    struct s_global *global;
    sem_t           *mutex;
    sem_t           *mutex_eat;    
}             t_philo;

typedef struct s_global
{
    int             n_philo;
    int             eat_count;
    int             eat_count_philo;
    u_int64_t       t_eat;
    u_int64_t       t_sleep;
    u_int64_t       t_die;
    u_int64_t       start;
    t_philo         *philo;
    char            *sem_print;
    char            *sem_dead;
    char            *sem_fork;
    sem_t           *mutex_forks; 
    sem_t           *mutex_print;
    sem_t           *mutex_dead;
}              t_global;


int         ft_strlen(char *str);
void	    ft_putnbr(int nb);
int         ft_atoi(const char *s);
int         main(int argc, char **argv);
int         init_philos(t_global *global);
char       *name(char *s1, char *dst, int num_philos);
int         start_threads(t_global *global);
void        *routine(void *philo_void);
void        *dead(void *philo_void);
void        life(t_philo *philo);
void        count(void *global_v);
u_int64_t   gettime(void);
int         print_ms(t_philo *philo, char *str, int n);


#endif