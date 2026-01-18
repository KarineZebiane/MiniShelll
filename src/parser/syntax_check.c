/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:14:41 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/09 18:10:05 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Check if a redirection operator has a file after it
*/
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

/*
** Main syntax checker
*/
int	ms_syntax_check(t_list *tokens)
{
	t_token	*token;
	t_token	*next;

	if (!tokens)
		return (0);
	token = (t_token *)tokens->content;
	if (token->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (0);
	}
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (ms_is_redir(token->type) && !check_redir_file(tokens))
			return (0);
		if (token->type == TOKEN_PIPE && tokens->next)
		{
			next = (t_token *)tokens->next->content;
			if (next->type == TOKEN_PIPE)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
				return (0);
			}
		}
		if (token->type == TOKEN_PIPE && !tokens->next)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
