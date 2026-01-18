/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:01:20 by kzebian           #+#    #+#             */
/*   Updated: 2026/01/09 18:09:26 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Check if character is whitespace.
*/
int	ms_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/*
** Check if character is a special operator character.
*/
int	ms_is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
** Check if character is a quote.
*/
int	ms_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/*
** Alias for is_special_char (for compatibility).
*/
int	ms_is_separator(char c)
{
	return (ms_is_special_char(c));
}
