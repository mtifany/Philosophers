/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/11 01:25:32 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"philo_bonus.h"

void	process(t_philo_args *args)
{
	int				i;

	i = -1;
	while (++i < args->table->ph_amount)
	{
		args->philosopher->pid_f[i] = fork();
		if (args->philosopher->pid_f[i] == 0)
			eat(&args[i]);
		if (args->philosopher->pid_f[i] == -1)
			ft_error("Error with creating process!");
	}
	wait(NULL);
	i = -1;
	while (++i < args->table->ph_amount)
	{
		kill(args->table->pid[i], 9);
	}
	free(args->philosopher->pid_f);
}

int	main(int argc, char **argv)
{
	t_philo_args	*args;
	t_philos		*phil;
	t_table			table;

	if (init_table(&table, argc, argv) != 0)
		return (1);
	if (init_philo(&phil, table.ph_amount, &(table.pid)) != 0)
		return (2);
	args = init_args(phil, table);
	if (args == NULL)
		return (3);
	if (init_semaphores(args) != 0)
		return (4);
	process(args);
	return (0);
}
