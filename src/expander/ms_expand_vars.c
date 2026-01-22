/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:49:33 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/21 22:04:43 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ms_append_char(char *str, char c)
{
	char	char_to_append[2];
	char	*tmp;

	char_to_append[0] = c;
	char_to_append[1] = '\0';
	tmp = ft_strjoin(str, char_to_append);
	free(str);
	return (tmp);
}

static char	*ms_expand_string(t_data *data, char *str)
{
	char	*new_str;
	char	quote_state;
	int		i;

	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	i = 0;
	quote_state = 0;
	while (str[i])
	{
		ms_update_quote_state(str[i], &quote_state);
		if (ms_should_expand(str, i, quote_state))
			new_str = ms_process_variable(data, str, &i, new_str);
		else
		{
			new_str = ms_append_char(new_str, str[i]);
			i++;
		}
	}
	return (new_str);
}

void	ms_expand_vars(t_data *data, t_command *cmd)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		expanded = ms_expand_string(data, cmd->args[i]);
		free(cmd->args[i]);
		cmd->args[i] = expanded;
		i++;
	}
}
