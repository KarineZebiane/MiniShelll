/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 23:14:38 by kzebian           #+#    #+#             */
/*   Updated: 2026/03/10 00:03:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_open_redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		return (-1);
	}
	return (fd);
}

int	ms_open_redir_out(char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		return (-1);
	}
	return (fd);
}
static int	ms_process_redir(t_redir *redir, int orig_stdin)
{
	if (redir->type == REDIR_IN)
		return (ms_handle_redir_in(redir));
	else if (redir->type == REDIR_OUT)
		return (ms_handle_redir_out(redir, 0));
	else if (redir->type == REDIR_APPEND)
		return (ms_handle_redir_out(redir, 1));
	else if (redir->type == REDIR_HEREDOC)
		return (ms_handle_heredoc(redir, orig_stdin));
	return (0);
}

int	ms_setup_redirections(t_command *cmd)
{
	t_list	*redir_list;
	t_redir	*redir;
	int		orig_stdin;   

	if (!cmd || !cmd->redirections)
		return (0);
	orig_stdin = dup(STDIN_FILENO);
	if (orig_stdin < 0)
		return (-1);
	redir_list = cmd->redirections;
	while (redir_list)
	{
		redir = (t_redir *)redir_list->content;
		if (ms_process_redir(redir, orig_stdin) < 0)
		{
			close(orig_stdin);
			return (-1);
		}
		redir_list = redir_list->next;
	}
	close(orig_stdin);
	return (0);
}
