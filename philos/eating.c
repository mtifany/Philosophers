/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/03 17:17:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"philo.h"

void	*eat(void *args)
{
	t_philo_args		*arg;

	arg = (t_philo_args *) args;
	if (arg->philosopher->name % 2 == 0)
		ft_usleep(arg->table->eat_time);
	while (!arg->table->end_flag)
	{
		take_fork(arg);
		eating(arg);
		sleeping(arg);
		if (arg->table->iters > 0 && arg->philosopher->eat_count >= \
		arg->table->iters)
			return (NULL);
		thinking(arg);
	}
	return (NULL);
}

void	take_fork(t_philo_args	*arg)
{
	pthread_mutex_lock(&arg->table->forks[arg->philosopher->left_fork]);
	printer(1, arg->philosopher->name, arg->table->start_time);
	pthread_mutex_lock(&arg->table->forks[arg->philosopher->right_fork]);
	printer(2, arg->philosopher->name, arg->table->start_time);
}

void	eating(t_philo_args	*arg)
{
	arg->philosopher->eat_count++;
	arg->philosopher->last_eat_time = time_ms();
	arg->philosopher->eating_flag = 1;
	printer(3, arg->philosopher->name, arg->table->start_time);
	ft_usleep(arg->table->eat_time);
	arg->philosopher->eating_flag = 0;
	pthread_mutex_unlock(&arg->table->forks[arg->philosopher->right_fork]);
	pthread_mutex_unlock(&arg->table->forks[arg->philosopher->left_fork]);
}

void	sleeping(t_philo_args	*arg)
{
	printer(4, arg->philosopher->name, arg->table->start_time);
	ft_usleep(arg->table->sleep_time);
}

void	thinking(t_philo_args	*arg)
{
	printer(5, arg->philosopher->name, arg->table->start_time);
}
