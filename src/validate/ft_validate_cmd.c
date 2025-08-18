/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:45:18 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 15:27:42 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"
#include "ft_printf.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	ft_validate_prog(t_list *cmd)
{
	t_pipe	*cur_process;
	if (!cmd || !cmd->content)
		return (0);
	while (cmd)
	{
		cur_process = cmd->content;
		if (!cur_process || !cur_process->cmdname)
			return (0);
		if (access(cur_process->cmdname, X_OK) != 0)
		{
			cur_process->to_exec = 0;
			ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n", strerror(errno),
				cur_process->cmdname);
			if (!cmd->next)
				exit(126);
		}
		cmd = cmd->next;
	}
	return (1);
}
