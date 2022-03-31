/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:24:12 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 16:36:41 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	size_t			eat_last;
	pthread_mutex_t	fork;
	struct s_philo	*r_philo;
	struct s_philo	*l_philo;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				t_die;
	int				t_eat;
	int				t_slp;
	int				n_eat;
	int				n_philos;
	int				max_eat;
	int				phil_die;
	size_t			t_init;
	t_philo			*philos;
	pthread_mutex_t	print;
	pthread_mutex_t	check;
}	t_data;

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_isspace(int c);

int		init_data(int argc, char *argv[], t_data *data);
void	print_status(t_philo *philo, int idmsg);
void	exit_philo(t_data *data, pthread_t *tid);
size_t	get_time(void);
void	add_sleep(t_data *data, size_t t_slp);

#endif
