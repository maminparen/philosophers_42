/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:54:30 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 16:54:32 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	size_t			eat_last;
	struct s_philo	*r_philo;
	struct s_philo	*l_philo;
	struct s_data	*data;
	pid_t			pid;
	pthread_t		find_die_philo;
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
	sem_t			*print;
	sem_t			*check;
	sem_t			*forks;
}	t_data;

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_isspace(int c);

int		init_data(int argc, char *argv[], t_data *data);

void	print_status(t_philo *philo, int idmsg);

void	exit_philo(t_data *data);
size_t	get_time(void);
void	add_sleep(t_data *data, size_t t_slp);

#endif
