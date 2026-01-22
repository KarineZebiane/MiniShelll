/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:55:29 by abkhoder          #+#    #+#             */
/*   Updated: 2026/01/21 22:21:12 by kzebian          ###   ########.fr       */
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

static int	ms_handle_exit_arg(t_data *data, char **args, int *exit_code)
{
	if (!ms_is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		*exit_code = 255;
		return (0);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		data->last_exit_code = 1;
		return (1);
	}
	*exit_code = ft_atoi(args[1]);
	return (0);
}

int	ms_builtin_exit(t_data *data, char **args)
{
	int	exit_code;

	exit_code = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (args[1])
	{
		if (ms_handle_exit_arg(data, args, &exit_code))
			return (1);
	}
	else
		exit_code = data->last_exit_code;
	ms_cleanup(data);
	exit(exit_code);
	return (0);
}
