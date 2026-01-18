/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afahs <afahs@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 07:29:40 by afahs             #+#    #+#             */
/*   Updated: 2025/05/24 02:00:40 by afahs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;
	size_t			i;

	i = 0;
	temp_dst = (unsigned char *) dst;
	temp_src = (unsigned char *) src;
	if (temp_dst > temp_src)
	{
		while (len > 0)
		{
			temp_dst[len - 1] = temp_src[len - 1];
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			temp_dst[i] = temp_src[i];
			i++;
		}
	}
	return (dst);
}
