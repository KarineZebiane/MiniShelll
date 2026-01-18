/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:40:57 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/16 14:56:53 by abkhoder         ###   ########.fr       */
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

static t_env	*ms_create_env_node_content(char *env_line)
{
	t_env	*new_env;
	char	*equal_sign;
	size_t	key_len;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
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
	{
		ms_free_env_node(new_env);
		return (NULL);
	}
	new_env->is_exported = 1;
	return (new_env);
}

t_list	*ms_create_env_list(char **envp)
{
	t_list	*env_list;
	t_list	*new_node;
	t_env	*env_content;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		env_content = ms_create_env_node_content(envp[i]);
		if (!env_content)
		{
			ft_lstclear(&env_list, ms_free_env_node);
			return (NULL);
		}
		new_node = ft_lstnew(env_content);
		if (!new_node)
		{
			ms_free_env_node(env_content);
			ft_lstclear(&env_list, ms_free_env_node);
			return (NULL);
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

char	*ms_get_env_value(t_list *env_list, const char *key)
{
	t_env	*env;

	while (env_list)
	{
		env = (t_env *)env_list->content;
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env_list = env_list->next;
	}
	return (NULL);
}
