/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/11 03:32:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"philo_bonus.h"

void	*eat(void *args)
{
	t_philo_args		*arg;

	arg = (t_philo_args *) args;
	if (pthread_create(&arg->philosopher->check_trd, NULL, checker, args) != 0)
		ft_error("Error while create monitor thread!");
	if (arg->philosopher->name % 2 == 0)
		ft_usleep(arg->table->eat_time);
	while (!arg->table->end_flag)
	{
		take_fork(arg);
		eating(arg);
		if (arg->table->iters > 0 && arg->philosopher->eat_count >= \
			arg->table->iters)
			break ;
		sleeping(arg);
		thinking(arg);
	}
	while (1)
		;
}

void	take_fork(t_philo_args	*arg)
{
	sem_wait(arg->table->eat_sem);
	sem_wait(arg->table->forks);
	printer(1, arg->philosopher->name, arg->table->start_time);
	sem_wait(arg->table->forks);
	printer(1, arg->philosopher->name, arg->table->start_time);
}

void	eating(t_philo_args	*arg)
{
	arg->philosopher->last_eat_time = time_ms();
	arg->philosopher->eating_flag = 1;
	arg->philosopher->eat_count++;
	printer(3, arg->philosopher->name, arg->table->start_time);
	sem_post(arg->table->eat_sem);
	ft_usleep(arg->table->eat_time);
	arg->philosopher->eating_flag = 0;
	sem_post(arg->table->forks);
	sem_post(arg->table->forks);
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
