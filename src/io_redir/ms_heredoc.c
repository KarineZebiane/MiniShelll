/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 23:15:04 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/23 16:50:43 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ms_heredoc_warning(void)
{
	ft_putendl_fd("minishell: warning: here-document delimited by EOF",
		STDERR_FILENO);
}

static int	ms_heredoc_read_line(char *delimiter, int write_fd)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		ms_heredoc_warning();
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
	return (0);
}

int	ms_do_heredoc(t_redir *redir)
{
	int		pipe_fds[2];
	char	*delimiter;

	delimiter = redir->file;
	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	ms_signals_heredoc();
	while (1)
	{
		if (ms_heredoc_read_line(delimiter, pipe_fds[1]))
			break ;
	}
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

static int	ms_heredoc_tmpfile_read(char *delimiter, int tmp_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	ms_do_heredoc_tmpfile(t_redir *redir)
{
	int		fd;
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
	ms_heredoc_tmpfile_read(delimiter, tmp_fd);
	close(tmp_fd);
	fd = open(tmpfile, O_RDONLY);
	unlink(tmpfile);
	return (fd);
}
