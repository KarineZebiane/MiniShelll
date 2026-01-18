/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:55:45 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/16 15:01:15 by abkhoder         ###   ########.fr       */
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

/* Handles the actual execution of an external command
This function is called inside a child process
data Main shell data , cmd Current command structure */
void	ms_execute_external(t_data *data, t_command *cmd)
{
	char	*path;
	char	**env_tab;

	ms_signals_child();
	path = ms_resolve_path(data, cmd->args[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		ms_cleanup(data);
		exit(127);
	}
	env_tab = ms_get_env_array(data->env_list);
	if (!env_tab)
	{
		free(path);
		ms_cleanup(data);
		exit(EXIT_FAILURE);
	}
	execve(path, cmd->args, env_tab);
	perror("minishell: execve");
	free(path);
	ft_free_array(env_tab);
	ms_cleanup(data);
	exit(126);
}

/* Forking logic for a single (non-piped) external command
data Main shell data 
cmd Current command structure  */
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
