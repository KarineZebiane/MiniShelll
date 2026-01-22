/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:20:00 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/21 22:24:26 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_update_env_node(t_list **env_list, char *key, char *value)
{
	t_list	*tmp;
	t_env	*env;

	tmp = *env_list;
	while (tmp)
	{
		env = (t_env *)tmp->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	env = malloc(sizeof(t_env));
	if (!env)
		return ;
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	ft_lstadd_back(env_list, ft_lstnew(env));
}

void	ms_remove_env_var(t_data *data, char *key)
{
	t_list	*curr;
	t_list	*prev;

	curr = data->env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(((t_env *)curr->content)->key, key) == 0)
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
}
