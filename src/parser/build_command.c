/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:13:43 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/21 21:48:31 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Convert token redirection type to redir type
*/
static t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return (REDIR_IN);
	else if (type == TOKEN_REDIRECT_OUT)
		return (REDIR_OUT);
	else if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	else
		return (REDIR_HEREDOC);
}

/*
** Add redirection to command
*/
static int	add_redir_to_cmd(t_command *cmd, t_list **tokens)
{
	t_token	*token;
	t_token	*file_token;
	t_redir	*redir;
	t_list	*redir_node;

	token = (t_token *)(*tokens)->content;
	*tokens = (*tokens)->next;
	file_token = (t_token *)(*tokens)->content;
	redir = ms_create_redir(get_redir_type(token->type), file_token->value);
	if (!redir)
		return (0);
	redir_node = ft_lstnew(redir);
	if (!redir_node)
	{
		free(redir->file);
		free(redir);
		return (0);
	}
	ft_lstadd_back(&(cmd->redirections), redir_node);
	return (1);
}

/*
** Fill args array with words from tokens
*/
static void	fill_args(t_command *cmd, t_list *tokens, int arg_count)
{
	t_token	*token;
	int		i;

	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return ;
	i = 0;
	while (tokens && i < arg_count)
	{
		token = (t_token *)tokens->content;
		if (token->type == TOKEN_PIPE)
			break ;
		if (token->type == TOKEN_WORD)
		{
			cmd->args[i] = ft_strdup(token->value);
			i++;
		}
		else if (ms_is_redir(token->type))
			tokens = tokens->next;
		tokens = tokens->next;
	}
	cmd->args[i] = NULL;
}

static int	ms_process_token(t_command *cmd, t_list **tokens)
{
	t_token	*token;

	token = (t_token *)(*tokens)->content;
	if (token->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		return (1);
	}
	if (ms_is_redir(token->type))
	{
		if (!add_redir_to_cmd(cmd, tokens))
			return (-1);
	}
	return (0);
}

t_command	*ms_build_single_command(t_list **tokens)
{
	t_command	*cmd;
	int			arg_count;
	t_list		*start;
	int			result;

	cmd = ms_create_command();
	if (!cmd)
		return (NULL);
	start = *tokens;
	arg_count = ms_count_args(*tokens);
	fill_args(cmd, start, arg_count);
	while (*tokens)
	{
		result = ms_process_token(cmd, tokens);
		if (result == 1)
			break ;
		if (result == -1)
			return (NULL);
		*tokens = (*tokens)->next;
	}
	return (cmd);
}
