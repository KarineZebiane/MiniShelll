/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 23:15:04 by kzebian           #+#    #+#             */
/*   Updated: 2026/03/10 01:16:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void ms_heredoc_warning(void)
{
	ft_putendl_fd("minishell: warning: here-document delimited by EOF",
				  STDERR_FILENO);
}

static int ms_heredoc_read_line(char *delimiter, int write_fd)
{
	char *line;

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

int ms_do_heredoc(t_redir *redir, int orig_stdin)
{
	int pipe_fds[2];
	char *delimiter;

	delimiter = redir->file;
	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	dup2(orig_stdin, STDIN_FILENO);
	ms_signals_heredoc();
	while (1)
	{
		if (ms_heredoc_read_line(delimiter, pipe_fds[1]))
			break;
	}
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

int ms_preprocess_heredocs(t_data *data)
{
	t_list *cmd_node;
	t_command *cmd;
	t_list *redir_node;
	t_redir *redir;   
	int         orig_stdin;

    orig_stdin = dup(STDIN_FILENO);
	cmd_node = data->command_list;
	while (cmd_node)
	{
		cmd = (t_command *)cmd_node->content;
		redir_node = cmd->redirections;
		while (redir_node)
		{
			redir = (t_redir *)redir_node->content;
			if (redir->type == REDIR_HEREDOC)
			{
				redir->fd = ms_do_heredoc(redir, orig_stdin);
				if (redir->fd < 0)
					return (-1);
			}
			redir_node = redir_node->next;
		}
		cmd_node = cmd_node->next;
	}
	return (0);
}
