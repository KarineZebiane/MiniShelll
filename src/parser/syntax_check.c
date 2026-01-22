/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:14:41 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/21 21:42:24 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redir_file(t_list *current)
{
	t_token	*token;
	t_token	*next_token;

	token = (t_token *)current->content;
	if (!current->next)
	{
		ft_putendl_fd("minishell: syntax error near redirection", 2);
		return (0);
	}
	next_token = (t_token *)current->next->content;
	if (next_token->type != TOKEN_WORD)
	{
		ft_putendl_fd("minishell: syntax error near redirection", 2);
		return (0);
	}
	return (1);
}

static int	check_consecutive_pipes(t_list *tokens)
{
	t_token	*token;
	t_token	*next;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->type == TOKEN_PIPE && tokens->next)
		{
			next = (t_token *)tokens->next->content;
			if (next->type == TOKEN_PIPE)
			{
				ft_putendl_fd("minishell: syntax error near token", 2);
				return (0);
			}
		}
		if (token->type == TOKEN_PIPE && !tokens->next)
		{
			ft_putendl_fd("minishell: syntax error near token", 2);
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

static int	check_pipe_syntax(t_list *tokens)
{
	t_token	*token;

	token = (t_token *)tokens->content;
	if (token->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		return (0);
	}
	return (check_consecutive_pipes(tokens));
}

int	ms_syntax_check(t_list *tokens)
{
	t_token	*token;

	if (!tokens)
		return (0);
	if (!check_pipe_syntax(tokens))
		return (0);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (ms_is_redir(token->type) && !check_redir_file(tokens))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
