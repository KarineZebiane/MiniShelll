/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:05:35 by afahs             #+#    #+#             */
/*   Updated: 2025/05/24 02:02:56 by afahs            ###   ########.fr       */
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
