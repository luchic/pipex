/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:19:44 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/22 15:27:38 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "ft_parse.h"
#include "libft.h"
#include <stdlib.h>

static void	ft_shift(char *str)
{
	char	c;

	while (*(str + 1))
	{
		c = *(str + 1);
		*str = c;
		str++;
	}
	*str = '\0';
}

static void	ft_parse_backslash(char *str)
{
	while (*str && ft_strchr(str, '\\') && ft_strchr(str + 1, '"'))
	{
		if (*str == '\\')
			ft_shift(str);
		str++;
	}
}

char	*ft_copy_until_quote(char *str, char ***args)
{
	char	*start;

	start = ++str;
	while (*str && *str != '\'')
		str++;
	start = ft_substr(start, 0, str - start);
	if (!start)
		return (NULL);
	if (ft_update_args(args, start) == -1)
	{
		free(start);
		return (NULL);
	}
	return (str + 1);
}

char	*ft_copy_until_delim(char *str, char ***args, char delim)
{
	char	*start;

	start = str;
	while (*str && *str != delim)
		str++;
	start = ft_substr(start, 0, str - start);
	if (!start)
		return (NULL);
	ft_parse_backslash(start);
	if (ft_update_args(args, start) == -1)
	{
		free(start);
		return (NULL);
	}
	return (str);
}

char	*ft_copy_until_double_quote(char *str, char ***args)
{
	char	*start;

	start = ++str;
	while (*str)
	{
		if (*str == '\"' && *(str - 1) != '\\')
			break ;
		str++;
	}
	start = ft_substr(start, 0, str - start);
	if (!start)
		return (NULL);
	ft_parse_backslash(start);
	if (ft_update_args(args, start) == -1)
	{
		free(start);
		return (NULL);
	}
	if (*str == '\0')
		return (str);
	return (str + 1);
}
