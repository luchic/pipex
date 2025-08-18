/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 19:19:44 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 20:56:15 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_utils.h"
#include <stdlib.h>

static void	ft_extract_cmd(char **cmd, char quote)
{
	int		count;
	char	*cpy;

	count = 0;
	while ((*cmd)[count] && (*cmd)[count] == quote)
		count++;
	cpy = ft_substr(*cmd, count, ft_strlen(*cmd) - 2 * count);
	free(*cmd);
	*cmd = cpy;
}

static void	ft_join_to(char **to, char *from)
{
	char	*tmp;

	if (!to || !from)
		return ;
	tmp = *to;
	*to = ft_strjoin(*to, from);
	free(tmp);
}

static char	*ft_join_cmds(int *i, char **args, char quote)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	while (args[*i + 1])
	{
		ft_join_to(&tmp, args[*i]);
		if (!tmp)
			return (NULL);
		ft_join_to(&tmp, " ");
		if (!tmp)
			return (NULL);
		(*i)++;
	}
	if (args[*i][ft_strlen(args[*i]) - 1] == quote)
	{
		ft_join_to(&tmp, args[*i]);
		if (!tmp)
			return (NULL);
		(*i) += 1;
	}
	ft_extract_cmd(&tmp, quote);
	return (tmp);
}

char	**ft_merge_qute(char **args, int size, char quote)
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
