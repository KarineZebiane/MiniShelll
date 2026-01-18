/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:14:07 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/09 18:09:56 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Check if token type is a redirection
*/
int	ms_is_redir(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

/*
** Create a new empty command
*/
t_command	*ms_create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->is_builtin = 0;
	cmd->pid = 0;
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
	return (cmd);
}

/*
** Create a redirection node
*/
t_redir	*ms_create_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

/*
** Count how many arguments we need (until pipe or end)
*/
int	ms_count_args(t_list *tokens)
{
	int		count;
	t_token	*token;

	count = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->type == TOKEN_PIPE)
			break ;
		if (token->type == TOKEN_WORD)
			count++;
		else if (ms_is_redir(token->type))
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
}
