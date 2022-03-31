/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:47:11 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 16:55:01 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*find_die_philo(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		sem_wait(data->check);
		if (get_time() - philo->eat_last > (size_t)data->t_die)
		{
			print_status(philo, 4);
			sem_wait(data->print);
			data->phil_die = 1;
			exit (1);
		}
		sem_post(data->check);
		if (data->phil_die)
			break ;
		usleep(1000);
		if (data->n_eat != -1 && philo->eat_count >= data->n_eat)
			break ;
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(philo->data->forks);
	print_status(philo, 0);
	if (philo->data->n_philos == 1)
	{
		add_sleep(data, data->t_die);
		print_status(philo, 4);
		data->phil_die = 1;
		return ;
	}
	sem_wait(philo->data->forks);
	print_status(philo, 0);
	sem_wait(philo->data->check);
	philo->eat_count++;
	print_status(philo, 1);
	philo->eat_last = get_time();
	sem_post(philo->data->check);
	add_sleep(data, data->t_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*philo_process(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->eat_last = data->t_init;
	pthread_create(&philo->find_die_philo, NULL, find_die_philo, (void *)philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!data->phil_die)
	{
		philo_eat(philo);
		if (data->n_eat != -1 && philo->eat_count >= data->n_eat)
			break ;
		print_status(philo, 2);
		add_sleep(data, data->t_slp);
		print_status(philo, 3);
	}
	pthread_join(philo->find_die_philo, NULL);
	exit (0);
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

	if ((argc < 5 || argc > 6) || init_data(argc, argv, &data))
		return (error_mesage());
	data.t_init = get_time();
	i = -1;
	while (++i < data.n_philos)
	{
		data.philos[i].pid = fork();
		if (data.philos[i].pid == -1)
		{
			write(2, "fork error\n", 19);
			exit(1);
		}
		if (data.philos[i].pid == 0)
			philo_process((void *)&data.philos[i]);
	}
	exit_philo(&data);
	return (0);
}
