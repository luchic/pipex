/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_proccess.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:30:10 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/20 10:49:55 by nluchini         ###   ########.fr       */
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
#include <sys/wait.h>

void	ft_run_fork(t_list *head, t_pipe *cur_process, char **envp)
{
	int	pid;

	if (cur_process->fd_inline == -1 || !cur_process->to_exec)
	{
		close(cur_process->fd_inline);
		close(cur_process->fd_outline);
		cur_process->fd_inline = -1;
		cur_process->fd_outline = -1;
		cur_process->pid = -1;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		ft_run_child(head, cur_process, envp);
	}
	else
	{
		close(cur_process->fd_inline);
		close(cur_process->fd_outline);
		cur_process->pid = pid;
	}
}

void	ft_wait_to(t_list *cmds)
{
	t_pipe	*cur_process;
	int		status;
	t_list	*head;

	head = cmds;
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
			{
				ft_lstclear(&head, ft_free_pipe);
				exit(WEXITSTATUS(status));
			}
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
		ft_run_fork(head, pp, envp);
		cmds = cmds->next;
	}
	ft_wait_to(head);
	return (0);
}
