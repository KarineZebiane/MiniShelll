/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:56:45 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/18 21:23:23 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_save_io(t_data *data)
{
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	if (data->stdin_backup < 0 || data->stdout_backup < 0)
	{
		perror("minishell: dup");
		exit(EXIT_FAILURE);
	}
}

void	ms_restore_io(t_data *data)
{
	if (data->stdin_backup != -1)
	{
		dup2(data->stdin_backup, STDIN_FILENO);
		close(data->stdin_backup);
	}
	if (data->stdout_backup != -1)
	{
		dup2(data->stdout_backup, STDOUT_FILENO);
		close(data->stdout_backup);
	}
}

void	ms_free_command_node(void *content)
{
	t_command	*cmd;
	int			i;

	cmd = (t_command *)content;
	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->redirections)
		ft_lstclear(&(cmd->redirections), ms_free_redir);
	free(cmd);
}

void	ms_init_data(t_data *data, char **envp)
{
	data->env_list = NULL;
	data->command_list = NULL;
	data->last_exit_code = 0;
	ms_save_io(data);
	data->env_list = ms_create_env_list(envp);
	if (!data->env_list)
	{
		ft_putendl_fd("minishell: WARNING: Could not initialize environment",
			STDERR_FILENO);
	}
}

void	ms_cleanup(t_data *data)
{
	if (data->env_list)
	{
		ft_lstclear(&(data->env_list), ms_free_env_node);
		data->env_list = NULL;
	}
	if (data->command_list)
	{
		ft_lstclear(&(data->command_list), ms_free_command_node);
		data->command_list = NULL;
	}
	if (data->stdin_backup != -1)
		close(data->stdin_backup);
	data->stdin_backup = -1;

	if (data->stdout_backup != -1)
		close(data->stdout_backup);
	data->stdout_backup = -1;
}
