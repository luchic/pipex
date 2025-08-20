/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:22:23 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 21:02:46 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_printf.h"
#include "ft_settings.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_validate_write_file(char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) != 0)
		{
			ft_std_errmsg(file);
			exit(EXIT_FAILURE);
		}
	}
}
