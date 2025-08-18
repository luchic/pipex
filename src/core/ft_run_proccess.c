/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_proccess.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:30:10 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 17:39:40 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_core.h"
#include "ft_pipe.h"
#include "ft_printf.h"
#include "ft_utils.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_run_fort(t_list *head, t_pipe *cur_process, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_run_child(head, cur_process, envp);
	}
	close(cur_process->fd_inline);
	close(cur_process->fd_outline);
	cur_process->pid = pid;
}

void	ft_wait_to(t_list *cmds)
{
	t_pipe	*cur_process;
	int		status;

	while (cmds)
	{
		cur_process = cmds->content;
		if (cur_process->pid > 0)
			waitpid(cur_process->pid, &status, 0);
		if (cmds->next)
		{
			cmds = cmds->next;
			continue ;
		}
		if (cur_process->fd_inline > 0 && WIFEXITED(status))
			if (WEXITSTATUS(status))
				exit(WEXITSTATUS(status));
		cmds = cmds->next;
	}
}

int	ft_run(t_list *cmds, int fd_inline, int fd_outline, char **envp)
{
	t_pipe	*pp;
	t_list	*head;

	head = cmds;
	pp = cmds->content;
	pp->fd_inline = fd_inline;
	pp = ft_lstlast(cmds)->content;
	pp->fd_outline = fd_outline;
	ft_set_pipes(cmds);
	while (cmds)
	{
		pp = cmds->content;
		ft_run_fort(head, pp, envp);
		cmds = cmds->next;
	}
	ft_wait_to(head);
	ft_lstclear(&head, ft_free_pipe);
	return (0);
}
