/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:23:37 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 17:38:56 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_philo(t_data *data, pthread_t *tid)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_join(tid[i], NULL);
	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&data->philos[i].fork);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->check);
	free(data->philos);
	free(tid);
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

void	print_status(t_philo *philo, int num)
{
	size_t	t;

	t = get_time() - philo->data->t_init;
	pthread_mutex_lock(&philo->data->print);
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
	pthread_mutex_unlock(&philo->data->print);
}
