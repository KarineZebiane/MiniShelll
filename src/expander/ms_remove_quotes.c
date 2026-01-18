/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:56:19 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/18 20:53:19 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ms_remove_quotes_from_string(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	in_quote;

	result = malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	
	i = 0;
	j = 0;
	in_quote = 0;
	
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && !in_quote)
		{
			result[j++] = str[i + 1];
			i += 2;
			continue;
		}		
		if (str[i] == '\\' && str[i + 1] && in_quote)
		{
			if (in_quote == '"' && (str[i + 1] == '"' || str[i + 1] == '$'))
			{
				result[j++] = str[i + 1];
				i += 2;
				continue;
			}
			result[j++] = str[i++];
			continue;
		}
		if ((str[i] == '\'' || str[i] == '"') && !in_quote)
		{
			in_quote = str[i];
			i++;
			continue;
		}
		if (str[i] == in_quote)
		{
			in_quote = 0;
			i++;
			continue;
		}
		result[j++] = str[i++];
	}
	
	result[j] = '\0';
	return (result);
}

void	ms_remove_quotes(t_command *cmd)
{
	int i;
	char *unquoted;
	char *old;

	i = 0;
	while (cmd->args[i])
	{
		old = cmd->args[i];
		unquoted = ms_remove_quotes_from_string(cmd->args[i]);
		cmd->args[i] = unquoted;
		free(old);
		i++;
	}
}