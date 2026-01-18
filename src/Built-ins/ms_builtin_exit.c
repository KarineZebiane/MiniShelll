/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkhoder <abkhoder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:55:29 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/16 10:32:49 by abkhoder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Checks if a string represents a valid numeric long long 
param str The string to check , return int 1 if numeric, 0 otherwise */
static int	ms_is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Implementation of the 'exit' builtin
Cleans up memory and exits the shell with a specific status.
param data Main shell data , param args Argument vector
return int Returns 1 only if it fails to exit (too many args) */
int	ms_builtin_exit(t_data *data, char **args)
{
	int	exit_code;

	exit_code = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (args[1])
	{
		if (!ms_is_numeric(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit_code = 255;
		}
		else if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			data->last_exit_code = 1;
			return (1);
		}
		else
			exit_code = ft_atoi(args[1]);
	}
	else
		exit_code = data->last_exit_code;
	ms_cleanup(data);
	exit(exit_code);
	return (0);
}
