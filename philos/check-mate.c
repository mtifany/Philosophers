/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check-mate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/03 17:17:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"philo.h"

int	ending(void *args)
{
	t_philo_args	*arg;
	int				i;
	int				number;

	arg = (t_philo_args *) args;
	if (arg->table->iters == -1 || arg->table->ph_amount == 1)
		return (1);
	number = 0;
	i = -1;
	while (++i < arg->table->ph_amount)
	{
		if (arg->philosopher[i].eat_count == arg->table->iters)
			number++;
	}
	if (number == arg->table->ph_amount)
	{
		ft_usleep(arg->table->eat_time - 10);
		return (0);
	}
	return (1);
}

void	*checker(void *args)
{
	t_philo_args		*arg;
	int					i;

	arg = (t_philo_args *) args;
	while (1)
	{
		i = -1;
		while (++i < arg->table->ph_amount)
		{
			if ((!(arg->philosopher[i].eating_flag) && (time_ms() - \
			arg->philosopher[i].last_eat_time) >= arg->table->die_time))
			{
				pthread_mutex_lock(arg->table->eat_mutex);
				arg->table->end_flag = 1;
				printer(6, arg->philosopher[i].name, arg->table->start_time);
				return (NULL);
			}
		}
		if (ending(args) == 0)
			return (NULL);
	}
}
