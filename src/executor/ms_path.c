/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:55:59 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/16 10:34:58 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ms_join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

static char	*ms_find_in_path(char **split_path, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (split_path[i])
	{
		full_path = ms_join_path(split_path[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*ms_get_path_var(t_list *env_list)
{
	t_env	*env;

	while (env_list)
	{
		env = (t_env *)env_list->content;
		if (strcmp(env->key, "PATH") == 0)
			return (env->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*ms_resolve_path(t_data *data, char *cmd)
{
	char	*path_var;
	char	**split_path;
	char	*resolved_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	else if (ft_strchr(cmd, '/'))
		return (NULL);
	path_var = ms_get_path_var(data->env_list);
	if (!path_var)
		return (NULL);
	split_path = ft_split(path_var, ':');
	if (!split_path)
		return (NULL);
	resolved_path = ms_find_in_path(split_path, cmd);
	ft_free_array(split_path);
	return (resolved_path);
}
