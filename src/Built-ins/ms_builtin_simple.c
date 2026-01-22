/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_simple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:55:38 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/19 15:32:30 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	ms_builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	perror("minishell: pwd");
	return (1);
}

int	ms_builtin_env(t_list *env_list)
{
	t_env	*env;

	while (env_list)
	{
		env = (t_env *)env_list->content;
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env_list = env_list->next;
	}
	return (0);
}

int	ms_builtin_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{	
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	ms_run_builtin(t_data *data, t_command *cmd)
{
	char	*name;

	name = cmd->args[0];
	if (ft_strcmp(name, "echo") == 0)
		return (ms_builtin_echo(cmd->args));
	if (ft_strcmp(name, "pwd") == 0)
		return (ms_builtin_pwd());
	if (ft_strcmp(name, "env") == 0)
		return (ms_builtin_env(data->env_list));
	if (ft_strcmp(name, "cd") == 0)
		return (ms_builtin_cd(data, cmd->args));
	if (ft_strcmp(name, "export") == 0)
		return (ms_builtin_export(data, cmd->args));
	if (ft_strcmp(name, "unset") == 0)
		return (ms_builtin_unset(data, cmd->args));
	if (ft_strcmp(name, "exit") == 0)
		return (ms_builtin_exit(data, cmd->args));
	return (1);
}
