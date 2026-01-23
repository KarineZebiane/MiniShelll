/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:40:36 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/23 20:40:38 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	x;
	char	i;
	long	n;

	n = nb;
	if (n < 0)
	{
		i = '-';
		write(fd, &i, 1);
		n = -n;
	}
	if (n / 10 <= 0)
	{
		i = n + '0';
		write(fd, &i, 1);
	}
	else
	{
		x = (n % 10) + '0';
		ft_putnbr_fd(n / 10, fd);
		write(fd, &x, 1);
	}
}
