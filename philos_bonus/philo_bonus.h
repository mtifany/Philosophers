/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/11 02:45:06 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>
# include <stddef.h>

typedef struct philosopher_tag {
	int			name;
	long long	last_eat_time;
	int			eating_flag;
	pid_t		*pid_f;
	pthread_t	check_trd;
	sem_t		*die_sem;
	int			eat_count;
}	t_philos;

typedef struct table_tag{
	long long	start_time;
	int			die_time;
	int			sleep_time;
	int			eat_time;
	int			ph_amount;
	int			fork_amount;
	int			iters;
	pid_t		*pid;
	sem_t		*forks;
	sem_t		*eat_sem;
	sem_t		*die_sem;
	int			end_flag;
}t_table;

typedef struct philo_args{
	t_philos	*philosopher;
	t_table		*table;
}	t_philo_args;

void			process(t_philo_args *args);

void			ft_usleep(uint64_t time_in_ms);
long long		time_ms(void);
void			printer(int operation, long long name, long long start);
long long		ft_parse(const char *str);
int				ft_error(char *str);

void			*checker(void *args);
int				init_philo(t_philos **phil, long long ph_amount, pid_t **pids);
int				init_table(t_table *table, int argc, char **argv);
t_philo_args	*init_args(t_philos *phil, t_table	table);
int				init_semaphores(void *args);

void			*eat(void *args);
void			take_fork(t_philo_args	*arg);
void			eating(t_philo_args	*arg);
void			sleeping(t_philo_args	*arg);
void			thinking(t_philo_args	*arg);
#endif //PHILO_BONUS_H
