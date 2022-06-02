/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/11 03:33:58 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"philo_bonus.h"

void	*checker(void *args)
{
	t_philo_args		*arg;

	arg = (t_philo_args *) args;
	while (1)
	{
		sem_wait(arg->table->die_sem);
		if (arg->philosopher->eat_count == arg->table->iters)
		{
			ft_usleep(arg->table->die_time);
			exit(EXIT_SUCCESS);
		}
		if (!(arg->philosopher->eating_flag) && (time_ms() - \
		arg->philosopher->last_eat_time) >= arg->table->die_time)
		{
			printer(6, arg->philosopher->name, arg->table->start_time);
			exit(EXIT_SUCCESS);
		}
		sem_post(arg->table->die_sem);
		usleep(1000);
	}
}

int	init_table(t_table *table, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		ft_error("Wrong arguments!");
	table->ph_amount = (int)ft_parse(argv[1]);
	table->fork_amount = (int)ft_parse(argv[1]);
	table->die_time = (int)ft_parse(argv[2]);
	table->eat_time = (int)ft_parse(argv[3]);
	table->sleep_time = (int)ft_parse(argv[4]);
	table->start_time = time_ms();
	table->iters = -1;
	if (argc == 6)
	{
		table->iters = (int)ft_parse(argv[5]);
		if (table->iters < 1)
			ft_error("Wrong arguments!");
	}
	if (table->ph_amount < 1 || table->die_time < 1 || table->sleep_time < 1 \
	|| table->eat_time < 1 || table->ph_amount > 200 || table->fork_amount < 1)
		ft_error("Wrong arguments!");
	return (0);
}

int	init_philo(t_philos **phil, long long ph_amount, pid_t **pid_arr)
{
	int	i;

	*pid_arr = (pid_t *) malloc(sizeof(pid_t) * ph_amount);
	if (*pid_arr == NULL)
		ft_error("Error while allocating pid array memory!");
	memset(*pid_arr, 0, ph_amount * sizeof(pid_t));
	*phil = (t_philos *)malloc(sizeof (t_philos) * ph_amount);
	if (*phil == NULL)
		ft_error("Error while allocating philos memory!");
	i = -1;
	while (++i < ph_amount)
	{
		(*phil)[i].name = i + 1;
		(*phil)[i].last_eat_time = time_ms();
		(*phil)[i].pid_f = &(*pid_arr[i]);
		(*phil)[i].eating_flag = 0;
		(*phil)[i].eat_count = 0;
	}
	return (0);
}

t_philo_args	*init_args(t_philos *phil, t_table	table)
{
	int				i;
	t_philo_args	*args;

	args = (t_philo_args *)malloc (sizeof(t_philo_args) * table.ph_amount);
	if (args == NULL)
		ft_error("Error while allocating args memory!");
	i = -1;
	while (++i < table.ph_amount)
	{
		args[i].philosopher = &phil[i];
		args[i].table = &table;
	}
	return (args);
}

int	init_semaphores(void *args)
{
	t_philo_args	*arg;
	unsigned int	amount;

	arg = (t_philo_args *) args;
	amount = (unsigned int) arg->table->ph_amount;
	sem_unlink("forks");
	sem_unlink("eat_sem");
	sem_unlink("die_sem");
	arg->table->forks = sem_open("forks", O_CREAT, 0644, amount);
	if (arg->table->forks == SEM_FAILED)
		ft_error("Error while opening semaphore!");
	arg->table->eat_sem = sem_open("eat_sem", O_CREAT, 0644, 1);
	if (arg->table->eat_sem == SEM_FAILED)
		ft_error("Error while opening semaphore!");
	arg->table->die_sem = sem_open("die_sem", O_CREAT, 0644, 1);
	if (arg->table->die_sem == SEM_FAILED)
		ft_error("Error while opening semaphore!");
	return (0);
}
