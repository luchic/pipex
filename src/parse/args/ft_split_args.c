/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:08:19 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 16:52:15 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"
#include "ft_printf.h"
#include "ft_settings.h"
#include "ft_utils.h"
#include "libft.h"
#include <stdlib.h>

static int	ft_check_if_quotes(char **args, char quote)
{
	char	*str;
	int		is_quote;
	int		i;

	is_quote = 0;
	i = 0;
	while (args[i])
	{
		str = args[i];
		if (str[0] == quote && !is_quote)
			is_quote = 1;
		if (str[ft_strlen(str) - 1] == quote && is_quote)
			return (1);
		i++;
	}
	return (0);
}

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

static void	ft_parse_backslash(char **args)
{
	char	*str;

	while (*args)
	{
		str = *args;
		while (*str && ft_strchr(str, '\\') && ft_strchr(str + 1, '"'))
		{
			if (*str == '\\')
				ft_shift(str);
			str++;
		}
		args++;
	}
}

char	**ft_split_args(char *str, char delim)
{
	char	**args;
	int		size;

	args = ft_split(str, delim);
	if (!args)
		return (NULL);
	size = 0;
	while (args[size])
		size++;
	ft_parse_backslash(args);
	if (ft_check_if_quotes(args, '\''))
		return (ft_merge_qute(args, size, '\''));
	if (ft_check_if_quotes(args, '\"'))
		return (ft_merge_qute(args, size, '\"'));
	return (args);
}
