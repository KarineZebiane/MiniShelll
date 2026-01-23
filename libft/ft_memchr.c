/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:39:47 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/23 20:39:48 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	t;
	unsigned char	*temp;

	t = (unsigned char)c;
	temp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (temp[i] == t)
			return ((void *)&temp[i]);
		i++;
	}
	return (NULL);
}
