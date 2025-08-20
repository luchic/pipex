/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errormsg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:54:20 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/20 11:38:23 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_settings.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

void	ft_print_errormsg(char *msg)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", PIPEX, msg);
}

void	ft_common_errormsg(void)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", PIPEX, strerror(errno));
}

void	ft_command_not_found_errormsg(char *cmd)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", PIPEX, cmd, CMD_NOTFOUND);
}

void	ft_std_errmsg(char *msg)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", PIPEX, msg, strerror(errno));
}
