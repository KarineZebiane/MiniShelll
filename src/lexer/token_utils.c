/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:03:15 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/16 16:29:27 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Create a new token (content only, no list node).
** To be wrapped in t_list node by caller.
*/
t_token	*ms_create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	return (token);
}

/*
** Free a single token (for ft_lstclear).
*/
void	ms_free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

/*
** Debug function: print all tokens.
*/
void	ms_print_tokens(t_list *tokens)
{
	const char	*type_names[] = {
		"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT",
		"APPEND", "HEREDOC", "WHITESPACE"
	};
	t_token		*token;

	ft_putendl_fd("\n=== TOKENS ===", STDOUT_FILENO);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		ft_putstr_fd("[", STDOUT_FILENO);
		ft_putstr_fd((char *)type_names[token->type], STDOUT_FILENO);
		ft_putstr_fd(": \"", STDOUT_FILENO);
		ft_putstr_fd(token->value, STDOUT_FILENO);
		ft_putendl_fd("\"]", STDOUT_FILENO);
		tokens = tokens->next;
	}
	ft_putendl_fd("==============\n", STDOUT_FILENO);
}
