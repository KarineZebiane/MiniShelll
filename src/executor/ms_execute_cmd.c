/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:55:45 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/21 22:15:16 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Converts our t_list environment into the char ** format for execve
env_list The linked list of environment variables
char** The array of "KEY=VALUE" strings, NULL terminated */
static char	**ms_get_env_array(t_list *env_list)
{
	char	**env_array;
	t_list	*tmp;
	t_env	*env;
	int		i;

	env_array = malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	if (!env_array)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		env = (t_env *)tmp->content;
		env_array[i] = ft_strjoin_three(env->key, "=", env->value);
		if (!env_array[i])
		{
			ft_free_array(env_array);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

static void	ms_exec_error_exit(t_data *data, char *cmd_name, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	if (exit_code == 127)
		ft_putendl_fd(": command not found", 2);
	else
		perror("");
	ms_cleanup(data);
	exit(exit_code);
}

void	ms_execute_external(t_data *data, t_command *cmd)
{
	char	*path;
	char	**env_tab;

	ms_signals_child();
	path = ms_resolve_path(data, cmd->args[0]);
	if (!path)
		ms_exec_error_exit(data, cmd->args[0], 127);
	env_tab = ms_get_env_array(data->env_list);
	if (!env_tab)
	{
		free(path);
		ms_cleanup(data);
		exit(EXIT_FAILURE);
	}
	execve(path, cmd->args, env_tab);
	free(path);
	ft_free_array(env_tab);
	ms_exec_error_exit(data, cmd->args[0], 126);
}

void	ms_execute_fork(t_data *data, t_command *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("minishell: fork");
		data->last_exit_code = 1;
		return ;
	}
	if (cmd->pid == 0)
	{
		if (ms_setup_redirections(cmd) != 0)
		{
			ms_cleanup(data);
			exit(EXIT_FAILURE);
		}
		ms_execute_external(data, cmd);
	}
	ms_wait_all(data);
}
