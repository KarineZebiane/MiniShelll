/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 23:15:04 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/16 13:49:28 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_do_heredoc(t_redir *redir)
{
	int		pipe_fds[2];
	char	*line;
	char	*delimiter;

	delimiter = redir->file;
		if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putendl_fd("minishell: warning: here-document delimited by end-of-file", STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fds[1], line, ft_strlen(line));
		write(pipe_fds[1], "\n", 1);
		free(line);
	}
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

int	ms_do_heredoc_tmpfile(t_redir *redir)
{
	int		fd;
	char	*line;
	char	*delimiter;
	char	*tmpfile;
	int		tmp_fd;

	delimiter = redir->file;
	tmpfile = "/tmp/minishell_heredoc_XXXXXX";
	tmp_fd = mkstemp(tmpfile);
	if (tmp_fd < 0)
	{
		perror("minishell: mkstemp");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	fd = open(tmpfile, O_RDONLY);
	unlink(tmpfile);
	return (fd);
}
