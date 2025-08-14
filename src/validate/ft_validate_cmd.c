/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:45:18 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/14 14:58:24 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"
#include "libft.h"
#include <unistd.h>

int ft_validate_prog(t_list *cmd)
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
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
