/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:37:11 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/18 19:29:03 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** The single allowed global variable (Subject requirement)
** Stores signal status for signal handling
*/
int	g_signal_status = 0;

/*
** The core execution loop of the shell.
** Prompts user, reads input, processes, and executes.
*/
static void	ms_shell_loop(t_data *data)
{
	char	*line;
	t_list	*tokens;

	while (1)
	{
		ms_setup_signals();
		line = readline(PROMPT);
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (line[0] == '\0' || ft_isspace_only(line))
		{
			free(line);
			continue ;
		}	
		add_history(line);
		tokens = ms_lexer(line);
		if (g_signal_status == 2)
		{
			data->last_exit_code = 130;
			g_signal_status = 0;
		}
		if (tokens)
			data->command_list = ms_parser(tokens);
		if (data->command_list)
		{
			t_list *cmd_node = data->command_list;
			while (cmd_node)
			{
				t_command *cmd = (t_command *)cmd_node->content;
				ms_expand_vars(data, cmd);
				ms_remove_quotes(cmd);
				cmd_node = cmd_node->next;
			}
		}
		if (data->command_list)
			ms_execute_manager(data);
		if (data->command_list)
		{
			ft_lstclear(&(data->command_list), ms_free_command_node);
			data->command_list = NULL;
		}
		if (tokens)
			ft_lstclear(&tokens, ms_free_token);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		exit_code;

	(void)argc;
	(void)argv;
	ms_init_data(&data, envp);
	ms_shell_loop(&data);	
	exit_code = data.last_exit_code;
	ms_cleanup(&data);
	return (exit_code);
}
