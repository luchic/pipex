/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:10:07 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/20 11:18:13 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_pipe.h"
#include "ft_settings.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_close_pipe(t_list *cmds)
{
	t_pipe	*pp;
	t_list	*cur;

	cur = cmds;
	while (cur)
	{
		pp = cur->content;
		if (pp->fd_inline != -1)
		{
			close(pp->fd_inline);
			pp->fd_inline = -1;
		}
		if (pp->fd_outline != -1)
		{
			close(pp->fd_outline);
			pp->fd_outline = -1;
		}
		cur = cur->next;
	}
}

void	ft_set_pipes(t_list *cmd)
{
	int		fd[2];
	t_pipe	*pp;
	t_list	*next;
	t_list	*cur;

	cur = cmd;
	next = cur->next;
	while (next)
	{
		if (pipe(fd) == -1)
		{
			ft_print_errormsg(PIPE_ERROR);
			exit(EXIT_FAILURE);
		}
		pp = cur->content;
		pp->fd_outline = fd[1];
		pp = next->content;
		pp->fd_inline = fd[0];
		cur = next;
		next = next->next;
	}
}
