/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/11 01:53:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"philo.h"

int	init_philo(t_philos **phil, long long ph_amount)
{
	int				i;

	*phil = (t_philos *)malloc(sizeof (t_philos) * ph_amount);
	if (*phil == NULL)
		return (ft_error("Error while allocating philos memory!", 1));
	i = -1;
	while (++i < ph_amount)
	{
		(*phil)[i].name = i + 1;
		(*phil)[i].right_fork = (i + 1) % ph_amount;
		(*phil)[i].left_fork = i;
		(*phil)[i].last_eat_time = time_ms();
		(*phil)[i].eating_flag = 0;
		(*phil)[i].eat_count = 0;
	}
	return (0);
}

int	init_mutexes(t_table *table)
{
	int	i;

	table->forks = malloc (sizeof(t_table) * table->ph_amount);
	if (!table->forks)
		return (ft_error("Error while allocating forks memory!", 1));
	table->eat_mutex = (pthread_mutex_t *) malloc (sizeof(t_table));
	if (pthread_mutex_init(table->eat_mutex, NULL) != 0)
		return (ft_error("Error while initializing eat mutex!", 1));
	i = -1;
	while (++i < table->ph_amount)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (ft_error("Error while initializing fork mutex!", 1));
	}
	return (0);
}

int	init_table(t_table *table, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_error("Wrong arguments!", 1));
	table->start_time = time_ms();
	table->ph_amount = ft_parse(argv[1]);
	table->die_time = ft_parse(argv[2]);
	table->eat_time = ft_parse(argv[3]);
	table->sleep_time = ft_parse(argv[4]);
	table->iters = -1;
	if (argc == 6)
	{
		table->iters = ft_parse(argv[5]);
		if (table->iters < 1)
			return (ft_error("Wrong arguments!", 1));
	}
	if (table->ph_amount < 1 || table->die_time < 1 || table->eat_time < 1 \
	|| table->sleep_time < 1 || table->ph_amount > 200)
		return (ft_error("Wrong arguments!", 1));
	if (init_mutexes(table) != 0)
		return (1);
	return (0);
}

t_philo_args	*init_args(t_philos *phil, t_table	table)
{
	int				i;
	t_philo_args	*args;

	args = malloc (sizeof(t_philo_args) * table.ph_amount);
	if (args == NULL)
		return (NULL);
	i = -1;
	while (++i < table.ph_amount)
	{
		args[i].philosopher = &phil[i];
		args[i].table = &table;
	}
	return (args);
}
