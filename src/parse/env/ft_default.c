/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:29:09 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 16:52:56 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_default_getenv(void)
{
	char	**envp;

	envp = ft_calloc(1, sizeof(char *));
	if (!envp)
		return (NULL);
	envp[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:\
		/sbin:/usr/local/munki:\
		/Library/Apple/usr/bin:/Library/Frameworks/Mono.framework/Versions/\
		Current/Commands");
	if (!envp[0])
	{
		free(envp);
		return (NULL);
	}
	return (envp);
}
