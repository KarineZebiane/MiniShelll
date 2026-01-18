/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:56:28 by afahs             #+#    #+#             */
/*   Updated: 2025/05/24 01:06:36 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	t;

	t = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == t)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == t)
		return ((char *)&s[i]);
	return (NULL);
}
