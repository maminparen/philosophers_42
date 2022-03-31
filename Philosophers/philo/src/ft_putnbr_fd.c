/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:25:35 by hzona             #+#    #+#             */
/*   Updated: 2021/11/17 16:34:13 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	min_null(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
		ft_putchar_fd('0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	num[10];

	if (n == 0 || n == -2147483648)
		return (min_null(n, fd));
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	i = 0;
	while (n > 0)
	{
		num[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		ft_putchar_fd(num[i], fd);
		i--;
	}
}
