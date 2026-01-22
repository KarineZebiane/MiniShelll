/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:03:10 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/21 21:53:24 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ms_handle_backslash(const char *str, int *i, char in_quote)
{
	if (str[*i] == '\\' && str[*i + 1] && !in_quote)
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}

static int	ms_handle_quote_char(const char *str, int *i, char *in_quote)
{
	if ((str[*i] == '\'' || str[*i] == '"') && !(*in_quote))
	{
		*in_quote = str[*i];
		(*i)++;
		return (1);
	}
	if (str[*i] == *in_quote)
	{
		*in_quote = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

char	*ms_extract_word(const char *str, int *i)
{
	int		start;
	char	in_quote;

	start = *i;
	in_quote = 0;
	while (str[*i])
	{
		if (ms_handle_backslash(str, i, in_quote))
			continue ;
		if (ms_handle_quote_char(str, i, &in_quote))
			continue ;
		if (!in_quote && (ms_is_whitespace(str[*i])
				|| ms_is_special_char(str[*i])))
			break ;
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

static t_token	*ms_create_double_op_token(const char *str, int *i)
{
	char	*value;

	value = ft_substr(str, *i, 2);
	(*i) += 2;
	if (value[0] == '<')
		return (ms_create_token(TOKEN_HEREDOC, value));
	else
		return (ms_create_token(TOKEN_APPEND, value));
}

t_token	*ms_tokenize_operator(const char *str, int *i)
{
	char	*value;

	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && str[*i
				+ 1] == '>'))
		return (ms_create_double_op_token(str, i));
	value = ft_substr(str, *i, 1);
	(*i)++;
	if (value[0] == '|')
		return (ms_create_token(TOKEN_PIPE, value));
	else if (value[0] == '<')
		return (ms_create_token(TOKEN_REDIRECT_IN, value));
	else
		return (ms_create_token(TOKEN_REDIRECT_OUT, value));
}
