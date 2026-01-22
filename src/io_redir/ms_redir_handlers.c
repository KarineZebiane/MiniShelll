/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:00:51 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/21 22:00:54 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_handle_redir_in(t_redir *redir)
{
	int	fd;

	fd = ms_open_redir_in(redir->file);
	if (fd < 0)
		return (-1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ms_handle_redir_out(t_redir *redir, int append)
{
	int	fd;

	fd = ms_open_redir_out(redir->file, append);
	if (fd < 0)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ms_handle_heredoc(t_redir *redir)
{
	int	fd;

	fd = ms_do_heredoc(redir);
	if (fd < 0)
		return (-1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}
