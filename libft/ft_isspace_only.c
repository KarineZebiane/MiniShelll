/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace_only.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/01/09 16:50:46 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Check if string contains only whitespace characters
** Returns 1 if only spaces/tabs/newlines, 0 otherwise
*/
int	ft_isspace_only(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}
