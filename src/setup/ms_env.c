/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:40:57 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/21 21:37:01 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_free_env_node(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

static int	ms_parse_env_line(t_env *new_env, char *env_line)
{
	char	*equal_sign;
	size_t	key_len;

	equal_sign = strchr(env_line, '=');
	if (equal_sign)
	{
		key_len = equal_sign - env_line;
		new_env->key = ft_substr(env_line, 0, key_len);
		new_env->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new_env->key = ft_strdup(env_line);
		new_env->value = ft_strdup("");
	}
	if (!new_env->key || !new_env->value)
		return (0);
	return (1);
}

static t_env	*ms_create_env_node_content(char *env_line)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	if (!ms_parse_env_line(new_env, env_line))
	{
		ms_free_env_node(new_env);
		return (NULL);
	}
	new_env->is_exported = 1;
	return (new_env);
}

static int	ms_add_env_node(t_list **env_list, char *env_str)
{
	t_list	*new_node;
	t_env	*env_content;

	env_content = ms_create_env_node_content(env_str);
	if (!env_content)
	{
		ft_lstclear(env_list, ms_free_env_node);
		return (0);
	}
	new_node = ft_lstnew(env_content);
	if (!new_node)
	{
		ms_free_env_node(env_content);
		ft_lstclear(env_list, ms_free_env_node);
		return (0);
	}
	ft_lstadd_back(env_list, new_node);
	return (1);
}

t_list	*ms_create_env_list(char **envp)
{
	t_list	*env_list;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		if (!ms_add_env_node(&env_list, envp[i]))
			return (NULL);
		i++;
	}
	return (env_list);
}
