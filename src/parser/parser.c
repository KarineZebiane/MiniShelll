/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:14:27 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/09 18:10:00 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Free redirection node
*/
void	ms_free_redir(void *content)
{
	t_redir	*redir;

	redir = (t_redir *)content;
	if (!redir)
		return ;
	free(redir->file);
	free(redir);
}

/*
** Main parser: converts token list to command list
*/
t_list	*ms_parser(t_list *tokens)
{
	t_list		*command_list;
	t_command	*cmd;
	t_list		*cmd_node;

	if (!ms_syntax_check(tokens))
		return (NULL);
	command_list = NULL;
	while (tokens)
	{
		cmd = ms_build_single_command(&tokens);
		if (!cmd)
		{
			ft_lstclear(&command_list, ms_free_command_node);
			return (NULL);
		}
		cmd_node = ft_lstnew(cmd);
		if (!cmd_node)
		{
			ms_free_command_node(cmd);
			ft_lstclear(&command_list, ms_free_command_node);
			return (NULL);
		}
		ft_lstadd_back(&command_list, cmd_node);
	}
	return (command_list);
}
