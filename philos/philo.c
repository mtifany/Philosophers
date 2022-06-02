/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/11 01:47:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"philo.h"

int	main(int argc, char **argv)
{
	t_philo_args	*args;
	t_philos		*phil;
	t_table			table;
	int				i;

	if (init_table(&table, argc, argv) != 0 || \
	init_philo(&phil, table.ph_amount) != 0)
		return (1);
	args = init_args(phil, table);
	if (args == NULL)
		return (1);
	i = -1;
	while (++i < table.ph_amount)
	{
		if (pthread_create(&phil[i].ph_thread, NULL, eat, &args[i]) != 0)
			return (1);
	}
	if (pthread_create(&args->philosopher->check_trd, NULL, checker, args) != 0)
		return (1);
	if (pthread_join(args->philosopher->check_trd, NULL) != 0)
		return (1);
	free(table.eat_mutex);
	free(table.forks);
	return (0);
}
