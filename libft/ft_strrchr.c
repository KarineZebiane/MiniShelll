/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:42:06 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/23 20:42:08 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	t;

	t = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == t)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
