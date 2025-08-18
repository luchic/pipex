/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:28:36 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 21:35:52 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"
#include "ft_printf.h"
#include "ft_utils.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_run_child(t_list *head, t_pipe *cur_process, char **envp)
{
	if (cur_process->fd_inline == -1 || !cur_process->to_exec)
	{
		ft_close_pipe(head);
		ft_lstclear(&head, ft_free_pipe);
		exit(0);
	}
	else
		dup2(cur_process->fd_inline, STDIN_FILENO);
	dup2(cur_process->fd_outline, STDOUT_FILENO);
	cur_process->fd_inline = -1;
	cur_process->fd_outline = -1;
	ft_close_pipe(head);
	if (execve(cur_process->cmdname, cur_process->args, envp) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", cur_process->args[0],
			strerror(errno));
		ft_lstclear(&head, ft_free_pipe);
		exit(2);
	}
}
