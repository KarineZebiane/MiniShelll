/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:05:23 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/21 22:07:52 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ms_replace_var(t_data *data, const char *key, int var_len)
{
	char	*var_name;
	char	*value;

	if (var_len == 1 && *key == '?')
		return (ft_itoa(data->last_exit_code));
	var_name = ft_substr(key, 0, var_len);
	if (!var_name)
		return (ft_strdup(""));
	value = ms_get_env_value(data->env_list, var_name);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

int	ms_get_var_len(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '?')
		return (1);
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}

char	*ms_process_variable(t_data *data, char *str, int *i, char *new_str)
{
	int		var_len;
	char	*value;
	char	*tmp;

	(*i)++;
	var_len = ms_get_var_len(str + *i);
	value = ms_replace_var(data, str + *i, var_len);
	tmp = ft_strjoin(new_str, value);
	free(new_str);
	free(value);
	*i += var_len;
	return (tmp);
}

int	ms_should_expand(char *str, int i, char quote_state)
{
	if (str[i] == '$' && quote_state != '\'' && str[i + 1] && (ft_isalnum(str[i
					+ 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		return (1);
	return (0);
}

void	ms_update_quote_state(char c, char *quote_state)
{
	if (c == '\'' || c == '"')
	{
		if (!(*quote_state))
			*quote_state = c;
		else if (*quote_state == c)
			*quote_state = 0;
	}
}
