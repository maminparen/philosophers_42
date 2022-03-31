/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:22:39 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 16:31:18 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_not_num(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '-')
			return (1);
		else if (argv[i][0] == '+')
			j++;
		if (!ft_isdigit(argv[i][j + 1]))
			return (1);
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

static int	is_minus(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (*s == '+' && s++)
		len--;
	while (*s == '0' && *s && len--)
		s++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (ft_strncmp(s, "2147483648", 10) >= 0)
		return (1);
	return (0);
}

static int	check_arg(int argc, char *argv[])
{
	int	i;

	if (is_not_num(argc, argv))
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (is_minus(argv[i]))
			return (1);
	}
	return (0);
}

void	init_data_next(t_data *data)
{
	int	i;

	data->phil_die = 0;
	data->max_eat = 0;
	data->philos = (t_philo *)malloc(data->n_philos * sizeof(t_philo));
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		if (i + 1 == data->n_philos)
			data->philos[i].r_philo = &data->philos[0];
		else
			data->philos[i].r_philo = &data->philos[i + 1];
		if (i == 0)
			data->philos[i].l_philo = &data->philos[data->n_philos - 1];
		else
			data->philos[i].l_philo = &data->philos[i - 1];
		pthread_mutex_init(&data->philos[i].fork, NULL);
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->check, NULL);
}

int	init_data(int argc, char *argv[], t_data *data)
{
	if (check_arg(argc, argv))
		return (1);
	data->n_philos = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_slp = ft_atoi(argv[4]);
	data->n_eat = -1;
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	init_data_next(data);
	return (0);
}
