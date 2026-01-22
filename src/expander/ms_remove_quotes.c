/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:56:19 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/21 20:04:12 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ms_handle_backslash(t_quote_ctx *ctx)
{
	if (ctx->str[ctx->i] == '\\' && ctx->str[ctx->i + 1] && !ctx->in_quote)
	{
		ctx->result[ctx->j++] = ctx->str[ctx->i + 1];
		ctx->i += 2;
		return (1);
	}
	if (ctx->str[ctx->i] == '\\' && ctx->str[ctx->i + 1] && ctx->in_quote)
	{
		if (ctx->in_quote == '"' && (ctx->str[ctx->i + 1] == '"'
				|| ctx->str[ctx->i + 1] == '$'))
		{
			ctx->result[ctx->j++] = ctx->str[ctx->i + 1];
			ctx->i += 2;
			return (1);
		}
		ctx->result[ctx->j++] = ctx->str[ctx->i++];
		return (1);
	}
	return (0);
}

static int	ms_handle_quote_toggle(t_quote_ctx *ctx)
{
	if ((ctx->str[ctx->i] == '\'' || ctx->str[ctx->i] == '"')
		&& !ctx->in_quote)
	{
		ctx->in_quote = ctx->str[ctx->i];
		ctx->i++;
		return (1);
	}
	if (ctx->str[ctx->i] == ctx->in_quote)
	{
		ctx->in_quote = 0;
		ctx->i++;
		return (1);
	}
	return (0);
}

static void	ms_process_char(t_quote_ctx *ctx)
{
	if (ms_handle_backslash(ctx))
		return ;
	if (ms_handle_quote_toggle(ctx))
		return ;
	ctx->result[ctx->j++] = ctx->str[ctx->i++];
}

static char	*ms_remove_quotes_from_string(char *str)
{
	t_quote_ctx	ctx;

	ctx.result = malloc(strlen(str) + 1);
	if (!ctx.result)
		return (NULL);
	ctx.str = str;
	ctx.i = 0;
	ctx.j = 0;
	ctx.in_quote = 0;
	while (ctx.str[ctx.i])
		ms_process_char(&ctx);
	ctx.result[ctx.j] = '\0';
	return (ctx.result);
}

void	ms_remove_quotes(t_command *cmd)
{
	int		i;
	char	*unquoted;
	char	*old;

	i = 0;
	while (cmd->args[i])
	{
		old = cmd->args[i];
		unquoted = ms_remove_quotes_from_string(cmd->args[i]);
		cmd->args[i] = unquoted;
		free(old);
		i++;
	}
}
