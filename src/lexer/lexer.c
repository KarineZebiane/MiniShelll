/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:01:37 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/16 16:26:58 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ms_lexer(const char *input)
{
	t_list		*token_list;
	t_token		*token_content;
	t_list		*new_node;
	int			i;
	char		*word;

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
		if (ms_is_special_char(input[i]))
			token_content = ms_tokenize_operator(input, &i);
		else
		{
			word = ms_extract_word(input, &i);
			token_content = ms_create_token(TOKEN_WORD, word);
		}
		if (!token_content)
		{
			ft_lstclear(&token_list, ms_free_token);
			return (NULL);
		}
		new_node = ft_lstnew(token_content);
		if (!new_node)
		{
			ms_free_token(token_content);
			ft_lstclear(&token_list, ms_free_token);
			return (NULL);
		}
		ft_lstadd_back(&token_list, new_node);
	}
	return (token_list);
}
