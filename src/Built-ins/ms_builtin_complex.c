/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_complex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:36:17 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/22 19:30:12 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Implementation of the 'cd' builtin
Changes directory and updates PWD/OLDPWD in environment.
param data Main shell data , param args Argument vector
return int 0 on success, 1 on failure */
int	ms_builtin_cd(t_data *data, char **args)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*target;

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		old_pwd[0] = '\0';
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		target = ms_get_env_value(data->env_list, "HOME");
	else
		target = args[1];
	if (!target || chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		if (target)
			perror(target);
		else
			ft_putendl_fd("HOME not set", 2);
		return (1);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
	{
		ms_update_env_node(&data->env_list, "OLDPWD", old_pwd);
		ms_update_env_node(&data->env_list, "PWD", new_pwd);
	}
	return (0);
}

/* Implementation of the 'unset' builtin
Removes a variable from the environment list.
param data Main shell data , param args Argument vector
return int Always 0 */
int	ms_builtin_unset(t_data *data, char **args)
{
	int		i;
	t_list	*curr;
	t_list	*prev;

	i = 1;
	while (args[i])
	{
		curr = data->env_list;
		prev = NULL;
		while (curr)
		{
			if (ft_strcmp(((t_env *)curr->content)->key, args[i]) == 0)
			{
				if (prev)
					prev->next = curr->next;
				else
					data->env_list = curr->next;
				ft_lstdelone(curr, ms_free_env_node);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
	return (0);
}

/*  'export' with no arguments (prints sorted env)
param env_list The environment list */
static void	ms_export_no_args(t_list *env_list)
{
	t_env	*env;

	while (env_list)
	{
		env = (t_env *)env_list->content;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		env_list = env_list->next;
	}
}

/* Implementation of the 'export' builtin
Adds or updates environment variables 
param data Main shell data , param args Argument vector
return int 0 on success, 1 on failure */
int	ms_builtin_export(t_data *data, char **args)
{
	int		i;
	char	*sep;
	char	*key;

	if (!args[1])
	{
		ms_export_no_args(data->env_list);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		sep = ft_strchr(args[i], '=');
		if (sep)
		{
			key = ft_substr(args[i], 0, sep - args[i]);
			ms_update_env_node(&data->env_list, key, sep + 1);
			free(key);
		}
		else
			ms_update_env_node(&data->env_list, args[i], NULL);
		i++;
	}
	return (0);
}
