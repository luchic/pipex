/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_errormsg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:54:20 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 16:59:39 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_settings.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

void	ft_open_file_errormsg(char *file)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", PIPEX, file, strerror(errno));
}

void	ft_open_pipe_errormsg(void)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", PIPEX, PIPE_ERROR);
}
