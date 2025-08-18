/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:08:19 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 15:13:33 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_settings.h"
#include "ft_utils.h"
#include "libft.h"
#include <stdlib.h>

// static char **ft_join_cmd_to_space(char *str, char *tmp)
// {

// }

static char	*ft_join_cmds(int *i, char **args, char quote)
{
	char	*tmp;
	char	*cpy;
	int count;
	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	count = 0;
	while (args[*i + 1] /* && args[*i][ft_strlen(args[*i]) - 1] != quote */)
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
	count = 0;
	while (tmp[count] && tmp[count] == quote)
		count++;
	cpy = ft_substr(tmp, count, ft_strlen(tmp) - 2 * count);
	free(tmp);

	return (cpy);
}

// static void ft_replace_marks(char *str)
// {
// 	while (*str)
// 	{
// 		if(*str == '\'')
// 			*str = '\"';
// 		str++;
// 	}
// }

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

void ft_shift(char *str)
{
	while (*(str + 1))
	{
		char c = *(str + 1);
		*str = c;
		str++;
	}
	*str = '\0';
}


void ft_parse_backslash(char **args)
{
	char *str;
	while(*args)
	{
		str = *args;
		while (*str && ft_strchr(str, '\\') && ft_strchr(str + 1, '"'))
		{
			if(*str == '\\')
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

	// ft_replace_marks(str);
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

// void print_args(char **args)
// {
// 	int i = 0;
// 	while (args[i])
// 	{
// 		ft_printf("args[%d]: %s\n", i, args[i]);
// 		i++;
// 	}

// }

// int main()
// {
// 	// char *t = 'awk '"'"'{count++} END {printf "count: %i", count}'"'"'';
// 	// char *str = "awk \"tmp\" \"{count++} END {printf \"count: %i\" , count}\"";
// 	char str[] = "awk \"{count++} END {print count}\"";
// 	char str2[] = "awk \"{count++} END {printf \"count: %i\" , count}\"";
// 	char str3[] = "awk '\"'\"'{count++} END {printf \"count: %i\", count}'\"'\"'";
// 	char **args;

// 	args = ft_split_args(str3, ' ');
// 	print_args(args);

// }