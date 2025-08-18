/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:42:53 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 16:58:33 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"
#include <stdlib.h>

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_pipe(void *cont)
{
	t_pipe	*pipe;
	int		i;

	pipe = (t_pipe *)cont;
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
