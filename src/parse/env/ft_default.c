/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:29:09 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/20 10:58:01 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_default_getenv(void)
{
	return (ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:\
		/sbin:/usr/local/munki:\
		/Library/Apple/usr/bin:/Library/Frameworks/Mono.framework/Versions/\
		Current/Commands"));
}
