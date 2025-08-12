/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:42:53 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/12 18:43:51 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"

void	ft_free_pipe(t_pipe *pipe)
{
	int	i;

	if (!pipe)
		return ;
	if (pipe->args)
	{
		i = -1;
		while (pipe->args[++i])
			free(pipe->args[i]);
		free(pipe->args);
	}
	if (pipe->cmdname)
		free(pipe->cmdname);
	free(pipe);
}
