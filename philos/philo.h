/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/03 16:54:14 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct philosopher_tag {
	pthread_t			check_trd;
	pthread_t			ph_thread;
	long long			name;
	unsigned int		left_fork;
	unsigned int		right_fork;
	long long			last_eat_time;
	int					eating_flag;
	int					eat_count;
}	t_philos;

typedef struct table_tag{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eat_mutex;
	long long		start_time;
	long long		die_time;
	long long		sleep_time;
	long long		eat_time;
	long long		ph_amount;
	long long		iters;
	int				end_flag;
}t_table;

typedef struct philo_args{
	t_philos		*philosopher;
	t_table			*table;
}	t_philo_args;

void			ft_usleep(uint64_t time_in_ms);
long long		time_ms(void);
void			printer(int operation, long long name, long long start);
long long		ft_parse(const char *str);
int				ft_error(char *str, int value);

int				ending(void *args);
void			*checker(void *args);

int				init_philo(t_philos **phil, long long ph_amount);
int				init_table(t_table *table, int argc, char **argv);
t_philo_args	*init_args(t_philos *phil, t_table	table);
int				init_mutexes(t_table *table);

void			*eat(void *args);
void			take_fork(t_philo_args	*arg);
void			eating(t_philo_args	*arg);
void			sleeping(t_philo_args	*arg);
void			thinking(t_philo_args	*arg);
#endif //PHILO_H
