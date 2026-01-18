/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:55:51 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/16 15:00:05 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Handles the execution of a single command.
If it's a built-in, it runs in the parent process (for things like cd/exit)
If it's external, it forks a child process, data The main shell structure
cmd The command to execute */
static void	ms_execute_single(t_data *data, t_command *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return ;
	if (ms_is_builtin(cmd->args[0]))
	{
		ms_save_io(data);
		if (ms_setup_redirections(cmd) == 0)
			data->last_exit_code = ms_run_builtin(data, cmd);
		ms_restore_io(data);
	}
	else
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			if (ms_setup_redirections(cmd) != 0)
				exit(EXIT_FAILURE);
			ms_execute_external(data, cmd);
		}
		else
		{
			waitpid(cmd->pid, &data->last_exit_code, 0);
		}
	}
}

/* The central manager for execution flow (P2.4)
Determines if we are running a single command or a pipeline
data The main shell structure containing the command list  */
void	ms_execute_manager(t_data *data)
{
	int	cmd_count;

	if (!data->command_list)
		return ;
	cmd_count = ft_lstsize(data->command_list);
	if (cmd_count == 1)
	{
		ms_execute_single(data, (t_command *)data->command_list->content);
	}
	else if (cmd_count > 1)
	{
		ms_execute_pipeline(data);
	}
}

/* Helper to wait for all child processes in a pipeline
Updates the last_exit_code based on the last command's status
data The main shell structure  */
void	ms_wait_all(t_data *data)
{
	t_list		*current;
	t_command	*cmd;
	int			status;

	current = data->command_list;
	while (current)
	{
		cmd = (t_command *)current->content;
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				data->last_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->last_exit_code = 128 + WTERMSIG(status);
		}
		current = current->next;
	}
}
