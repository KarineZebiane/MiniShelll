/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzebian <kzebian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:01:16 by kzebian           #+#    #+#             */
/*   Updated: 2025/12/26 16:10:50 by kzebian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Print error message and exit.
*/
void	ms_error_exit(const char *msg, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
	exit(exit_code);
}

/*
** Print error message for a command.
*/
void	ms_print_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}
