/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:53:07 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/21 21:53:09 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_handle_quotes(const char *s, int i, char quote_type)
{
	int	end;

	end = i + 1;
	while (s[end] && s[end] != quote_type)
		end++;
	if (s[end] == quote_type)
		return (end);
	return (i);
}
