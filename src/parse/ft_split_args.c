/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:08:19 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/15 19:39:40 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_settings.h"
#include "ft_utils.h"
#include "libft.h"
#include <stdlib.h>

static char	*ft_join_cmds(int *i, char **args, char quote)
{
	char	*tmp;
	char	*cpy;

	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	while (args[*i] && args[*i][ft_strlen(args[*i]) - 1] != quote)
	{
		cpy = tmp;
		tmp = ft_strjoin(tmp, args[*i]);
		free(cpy);
		if (!tmp)
			return (NULL);
		cpy = tmp;
		tmp = ft_strjoin(tmp, " ");
		free(cpy);
		if (!tmp)
			return (NULL);
		(*i)++;
	}
	if (args[*i][ft_strlen(args[*i]) - 1] == quote)
	{
		cpy = tmp;
		tmp = ft_strjoin(tmp, args[*i]);
		free(cpy);
		if (!tmp)
			return (NULL);
		(*i) += 1;
	}
	cpy = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
	free(tmp);
	if (cpy[0] == '\'' && cpy[ft_strlen(cpy) - 1] == '\'')
	{
		tmp = ft_substr(cpy, 1, ft_strlen(cpy) - 2);
		free(cpy);
		cpy = tmp;
	}
	return (cpy);
}

static char	**ft_merge_qute(char **args, int size, char quote)
{
	char	**new_args;
	int		i;
	int		j;

	new_args = ft_calloc(size + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (args[i][0] == quote)
		{
			new_args[j++] = ft_join_cmds(&i, args, quote);
			if (!new_args[j - 1])
				return (ft_free_split(new_args), NULL);
		}
		else
			new_args[j++] = ft_strdup(args[i++]);
	}
	new_args[j] = NULL;
	return (new_args);
}

static int	ft_check_if_quotes(char **args, char quote)
{
	char	*str;
	int		is_quote;
	int		j;
	int		i;

	is_quote = 0;
	i = 0;
	j = 0;
	while (args[i])
	{
		str = args[i];
		if (str[0] == quote && !is_quote)
		{
			is_quote = 1;
			j = i;
		}
		else if (str[ft_strlen(str) - 1] == quote && is_quote)
		{
			return (i - j);
		}
		i++;
	}
	return (0);
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
	if (ft_check_if_quotes(args, '\''))
		return (ft_merge_qute(args, size, '\''));
	if (ft_check_if_quotes(args, '\"'))
		return (ft_merge_qute(args, size, '\"'));
	return (args);
}

// void print_args(char **args)
// {
// 	int i = 0;
// 	while (args[i])
// 	{
// 		ft_printf("%s\n", args[i]);
// 		i++;
// 	}

// }

// int main()
// {
// 	char *str = "grep -v 'u y'";
// 	char **args;

// 	args = ft_split_args(str, ' ');
// 	print_args(args);

// }