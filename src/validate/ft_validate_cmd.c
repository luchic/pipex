/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:45:18 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 17:27:16 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_pipe.h"
#include "ft_printf.h"
#include "ft_settings.h"
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_validate_cmd_if_exist(t_list *cmds)
{
	t_pipe	*cur_process;

	if (!cmds || !cmds->content)
		return (0);
	while (cmds)
	{
		cur_process = cmds->content;
		if (!cur_process->cmdname)
			ft_command_not_found_errormsg(cur_process->args[0]);
		if (!cmds->next && !cur_process->cmdname)
			exit(NOT_EXIST_ERROR);
		cmds = cmds->next;
	}
	return (1);
}

int	ft_validate_cmd_permisions(t_list *cmds)
{
	t_pipe	*cur_process;

	if (!cmds || !cmds->content)
		return (0);
	while (cmds)
	{
		cur_process = cmds->content;
		if (!cur_process || !cur_process->cmdname)
			return (0);
		if (access(cur_process->cmdname, X_OK) != 0)
		{
			cur_process->to_exec = 0;
			ft_std_errmsg(cur_process->cmdname);
			if (!cmds->next)
				exit(126);
		}
		cmds = cmds->next;
	}
	return (1);
}
