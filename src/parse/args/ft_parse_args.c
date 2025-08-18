/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:51:31 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 19:07:58 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"
#include "ft_parse.h"
#include "ft_settings.h"
#include "libft.h"
#include "ft_utils.h"
#include <stdlib.h>

static t_pipe	*ft_pipe_node(char *args)
{
	t_pipe	*npipe;

	npipe = ft_calloc(1, sizeof(t_pipe));
	if (!npipe)
		return (NULL);
	npipe->args = ft_split_args(args, CMD_DELIM);
	npipe->fd_inline = -1;
	npipe->fd_outline = -1;
	npipe->pid = -1;
	return (npipe);
}

t_list	*ft_parse_args(int argc, char **argv)
{
	t_list	*head;
	t_list	*new_node;
	t_pipe	*npipe;
	int		i;

	i = 0;
	head = NULL;
	while (i < argc)
	{
		npipe = ft_pipe_node(argv[i]);
		if (!npipe)
			return (ft_lstclear(&head, ft_free_pipe), NULL);
		new_node = ft_lstnew(npipe);
		if (!new_node)
		{
			ft_free_pipe(npipe);
			return (ft_lstclear(&head, ft_free_pipe), NULL);
		}
		ft_lstadd_back(&head, new_node);
		i++;
	}
	return (head);
}
