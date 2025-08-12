/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:57:11 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/12 13:05:04 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_settings.h"
#include "libft.h"

static char	*ft_getenv(char **envp)
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, PATH, ft_strlen(PATH)) == 0)
			return (*envp + ft_strlen(PATH));
		envp++;
	}
	return (NULL);
}

char	**ft_getenv_paths(char **envp)
{
	char	*path_value;
	char	**paths;

	path_value = ft_getenv(envp);
	if (!path_value)
		return (NULL);
	return (ft_split(path_value, PATH_DELIM));
}
