/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:01:37 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/21 21:48:19 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*ms_get_next_token(const char *input, int *i)
{
	t_token	*token_content;
	char	*word;

	if (ms_is_special_char(input[*i]))
		token_content = ms_tokenize_operator(input, i);
	else
	{
		word = ms_extract_word(input, i);
		token_content = ms_create_token(TOKEN_WORD, word);
	}
	return (token_content);
}

static int	ms_add_token_to_list(t_list **token_list, t_token *token_content)
{
	t_list	*new_node;

	if (!token_content)
	{
		ft_lstclear(token_list, ms_free_token);
		return (0);
	}
	new_node = ft_lstnew(token_content);
	if (!new_node)
	{
		ms_free_token(token_content);
		ft_lstclear(token_list, ms_free_token);
		return (0);
	}
	ft_lstadd_back(token_list, new_node);
	return (1);
}

t_list	*ms_lexer(const char *input)
{
	t_list	*token_list;
	t_token	*token_content;
	int		i;

	if (ms_has_unclosed_quotes(input))
	{
		ms_print_error(NULL, "syntax error: unclosed quotes");
		return (NULL);
	}
	token_list = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && ms_is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		token_content = ms_get_next_token(input, &i);
		if (!ms_add_token_to_list(&token_list, token_content))
			return (NULL);
	}
	return (token_list);
}
