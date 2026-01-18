/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 23:57:44 by afahs             #+#    #+#             */
/*   Updated: 2025/05/24 03:38:16 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*res;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] && inset(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (start <= end && inset(s1[end], set))
		end--;
	res = (char *)malloc(end - start + 2);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + start, (end - start + 2));
	return (res);
}
