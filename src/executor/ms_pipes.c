/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:56:07 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/16 14:26:56 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Handles the redirection of FDs 
inside the child process
If there's a previous pipe, it connects STDIN to it
If there's a next pipe, it connects STDOUT to it , prev_fd The read end of the previous pipe
pipe_fds The current pipe [read, write]
is_last Boolean flag for the last command in the pipeline */
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

/* Logic for a single child process within a pipeline
Sets up signals, redirections, and executes the command
data Main data structure,  cmd Current command struct
p_fds Array containing [prev_pipe_read_fd
current_pipe_read, write], is_last Boolean flag */
static void	ms_child_pipeline(t_data *data, t_command *cmd, int *p_fds, int is_last)
{
	ms_pipe_redirect(p_fds[0], &p_fds[1], is_last);
	if (ms_setup_redirections(cmd) != 0)
		exit(EXIT_FAILURE);
	if (ms_is_builtin(cmd->args[0]))
		exit(ms_run_builtin(data, cmd));
	ms_execute_external(data, cmd);
}

/* Iterates through the command list and
forks processes for each pipe,data Main shell structure
prev_fd The read end of the previous pipe (starts at -1)
current Pointer to the current command in the list */
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
		if (prev_fd != -1)
			close(prev_fd);
		if (current->next)
		{
			close(pipe_fds[1]);
			prev_fd = pipe_fds[0];
		}
		else
			prev_fd = -1;
		current = current->next;
	}
}

/* Entry point for pipeline execution
Creates the chain of processes and waits for them to finish
data The main shell structure */
void	ms_execute_pipeline(t_data *data)
{
	if (!data->command_list)
		return ;
	ms_fork_pipeline(data, -1, data->command_list);
	ms_wait_all(data);
}
