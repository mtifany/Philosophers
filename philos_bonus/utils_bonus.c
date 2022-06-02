/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/03 16:02:34 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"philo_bonus.h"

void	ft_usleep(uint64_t time_in_ms)
{
	uint64_t	start_time;

	start_time = time_ms();
	while ((time_ms() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

long long	time_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	printer(int operation, long long name, long long start)
{
	long long	time;

	time = time_ms() - start;
	if (operation == 1)
		printf("[%lld] ms %lld has taken fork \n", time, name);
	if (operation == 3)
		printf("[%lld] ms %lld is eating \n", time, name);
	if (operation == 4)
		printf("[%lld] ms %lld is sleeping \n", time, name);
	if (operation == 5)
		printf("[%lld] ms %lld is thinking \n", time, name);
	if (operation == 6)
		printf("[%lld] ms %lld died \n", time, name);
}

long long	ft_parse(const char *str)
{
	unsigned long long	res;
	int					i;

	i = 0;
	res = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if ((res > 9223372036854775807))
			return (-1);
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	return ((long long)res);
}

int	ft_error(char *str)
{
	printf("%s", str);
	exit (EXIT_FAILURE);
}
