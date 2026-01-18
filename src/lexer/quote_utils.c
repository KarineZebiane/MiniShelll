/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:01:35 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/09 19:09:46 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_has_unclosed_quotes(const char *str)
{
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i += 2;
			continue ;
		}
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}
