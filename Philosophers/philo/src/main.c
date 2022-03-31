/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:22:46 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 17:06:57 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	find_die_philo(t_data *data)
{
	int	i;

	while (!data->max_eat)
	{
		i = -1;
		while (!data->phil_die && ++i < data->n_philos)
		{
			pthread_mutex_lock(&data->check);
			if (get_time() - data->philos[i].eat_last > (size_t)data->t_die)
			{
				print_status(&data->philos[i], 4);
				data->phil_die = 1;
			}
			pthread_mutex_unlock(&data->check);
			usleep(100);
		}
		if (data->phil_die)
			break ;
		i = 0;
		while (data->n_eat != -1 && i < data->n_philos
			&& data->philos[i].eat_count >= data->n_eat)
			i++;
		if (i == data->n_philos)
			data->max_eat = 1;
	}
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->fork);
	print_status(philo, 0);
	if (philo->data->n_philos == 1)
	{
		add_sleep(data, data->t_die);
		print_status(philo, 4);
		pthread_mutex_unlock(&philo->fork);
		data->phil_die = 1;
		return ;
	}
	pthread_mutex_lock(&philo->r_philo->fork);
	print_status(philo, 0);
	pthread_mutex_lock(&data->check);
	philo->eat_count++;
	print_status(philo, 1);
	philo->eat_last = get_time();
	pthread_mutex_unlock(&data->check);
	add_sleep(data, data->t_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->r_philo->fork);
}

void	*philo_process(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!data->phil_die && !data->max_eat)
	{
		philo_eat(philo);
		print_status(philo, 2);
		add_sleep(data, data->t_slp);
		print_status(philo, 3);
	}
	return (NULL);
}

int	error_mesage(void)
{
	write(2, "Error: invalid arguments\n", 25);
	write(2, "Write: ./philo [philo count] [time die] [time eat]", 49);
	write(2, " [time sleep] [max eat]\n", 24);
	exit(1);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_data		data;
	pthread_t	*tid;

	if ((argc < 5 || argc > 6) || init_data(argc, argv, &data))
		return (error_mesage());
	tid = (pthread_t *)malloc(data.n_philos * sizeof(pthread_t));
	data.t_init = get_time();
	i = -1;
	while (++i < data.n_philos)
	{
		if (pthread_create(&tid[i], NULL, &philo_process, &data.philos[i]))
		{
			write(2, "Error: cannot create thread\n", 28);
			free(data.philos);
			free(tid);
			return (1);
		}
		pthread_mutex_lock(&data.check);
		data.philos[i].eat_last = data.t_init;
		pthread_mutex_unlock(&data.check);
	}
	find_die_philo(&data);
	exit_philo(&data, tid);
	return (0);
}
