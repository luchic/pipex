/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:23:24 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/22 15:26:59 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_update_args(char ***args, char *str)
{
	static int	size = 0;
	static int	copasity = 0;
	char		**tmp;

	if (!*args)
	{
		copasity = 8;
		size = 0;
		*args = ft_calloc(copasity + 1, sizeof(char *));
		if (!*args)
			return (-1);
	}
	if (size + 1 >= copasity)
	{
		tmp = ft_realloc(*args, copasity + 1, (2 * copasity + 1)
				* sizeof(char *));
		if (!tmp)
			return (-1);
		copasity *= 2;
		*args = tmp;
	}
	(*args)[size] = str;
	size++;
	return (0);
}
