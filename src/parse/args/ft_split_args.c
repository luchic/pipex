/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:08:19 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/22 15:22:28 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"
#include "ft_printf.h"
#include "ft_settings.h"
#include "ft_utils.h"
#include "libft.h"
#include <stdlib.h>

char	**simple_get_args(char *str, char delim)
{
	char	**args;

	args = NULL;
	while (*str)
	{
		while (*str && *str == delim)
			str++;
		if (!*str)
			break ;
		if (*str == '\'')
			str = ft_copy_until_quote(str, &args);
		else if (*str == '\"')
			str = ft_copy_until_double_quote(str, &args);
		else
			str = ft_copy_until_delim(str, &args, delim);
		if (!str)
			return (ft_free_split(args), NULL);
	}
	return (args);
}

char	**ft_split_args(char *str, char delim)
{
	int	flags;
	int	i;

	i = 0;
	flags = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '\\')
			flags = 1;
		i++;
	}
	if (!flags)
		return (ft_split(str, delim));
	else
		return (simple_get_args(str, delim));
}

// #include <stdio.h>

// int main(int argc, char **argv)
// {
// 	// char *args = "Hello '\"World\"' \"'This is a test'\" \"Cat
//	//	+ Dog is \\\"Nap\\\"";
// 	char *args = "./script\"quote.sh";
// 	char **result = ft_split_args(args, ' ');
// 	if (!result)
// 	{
// 		ft_printf("Error: Memory allocation failed.\n");
// 		return (1);
// 	}
// 	for (int i = 0; result[i]; i++)
// 	{
// 		ft_printf("Arg [%d]: %s\n", i, result[i]);
// 		free(result[i]);
// 	}
// 	free(result);
// 	return (0);
// }
