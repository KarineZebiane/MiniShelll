/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:56:07 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/21 22:17:13 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ms_pipe_redirect(int prev_fd, int *pipe_fds, int is_last)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (!is_last)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
}

static void	ms_child_pipeline(t_data *data, t_command *cmd, int *p_fds,
		int is_last)
{
	ms_pipe_redirect(p_fds[0], &p_fds[1], is_last);
	if (ms_setup_redirections(cmd) != 0)
		exit(EXIT_FAILURE);
	if (ms_is_builtin(cmd->args[0]))
		exit(ms_run_builtin(data, cmd));
	ms_execute_external(data, cmd);
}

static void	ms_handle_parent_pipe(int *prev_fd, int *pipe_fds, int has_next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next)
	{
		close(pipe_fds[1]);
		*prev_fd = pipe_fds[0];
	}
	else
		*prev_fd = -1;
}

static void	ms_fork_pipeline(t_data *data, int prev_fd, t_list *current)
{
	int			pipe_fds[2];
	int			p_params[3];
	t_command	*cmd;

	while (current)
	{
		cmd = (t_command *)current->content;
		if (current->next && pipe(pipe_fds) == -1)
			return (perror("minishell: pipe"));
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			p_params[0] = prev_fd;
			p_params[1] = pipe_fds[0];
			p_params[2] = pipe_fds[1];
			ms_child_pipeline(data, cmd, p_params, current->next == NULL);
		}
		ms_handle_parent_pipe(&prev_fd, pipe_fds, current->next != NULL);
		current = current->next;
	}
}

void	ms_execute_pipeline(t_data *data)
{
	if (!data->command_list)
		return ;
	ms_fork_pipeline(data, -1, data->command_list);
	ms_wait_all(data);
}
