/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:21:07 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 16:31:16 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_settings.h"
#include <fcntl.h>

int	ft_get_readfile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

int	ft_get_writefile(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}
