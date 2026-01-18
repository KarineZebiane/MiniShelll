/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 23:14:38 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/04 23:22:04 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ms_open_redir_in(char *file)
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

static int	ms_open_redir_out(char *file, int append)
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

int	ms_setup_redirections(t_command *cmd)
{
	t_list	*redir_list;
	t_redir	*redir;
	int		fd;

	if (!cmd || !cmd->redirections)
		return (0);
	redir_list = cmd->redirections;
	while (redir_list)
	{
		redir = (t_redir *)redir_list->content;
		if (redir->type == REDIR_IN)
		{
			fd = ms_open_redir_in(redir->file);
			if (fd < 0)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = ms_open_redir_out(redir->file, 0);
			if (fd < 0)
				return (-1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = ms_open_redir_out(redir->file, 1);
			if (fd < 0)
				return (-1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			fd = ms_do_heredoc(redir);
			if (fd < 0)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir_list = redir_list->next;
	}
	return (0);
}
