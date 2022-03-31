/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:50:51 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 17:39:18 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, int num)
{
	size_t	t;

	t = get_time() - philo->data->t_init;
	sem_wait(philo->data->print);
	if (!philo->data->phil_die && !philo->data->max_eat)
	{
		printf("%ld", t);
		printf(" %d ", philo->id);
		if (num == 0)
			printf("has taken a fork");
		if (num == 1)
			printf("is eating");
		if (num == 2)
			printf("is sleeping");
		if (num == 3)
			printf("is thinking");
		if (num == 4)
			printf("died");
		printf("\n");
	}
	sem_post(philo->data->print);
}

void	exit_philo(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->n_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < data->n_philos)
				kill(data->philos[i].pid, SIGKILL);
			break ;
		}
	}
	sem_close(data->print);
	sem_close(data->check);
	sem_close(data->forks);
	sem_unlink("/sem_print");
	sem_unlink("/sem_check");
	sem_unlink("/sem_forks");
	free(data->philos);
}

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	add_sleep(t_data *data, size_t t_slp)
{
	size_t	t;

	t = get_time();
	while (!(data->phil_die))
	{
		if (get_time() - t >= t_slp)
			break ;
		usleep(100);
	}
}
