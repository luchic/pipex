/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:07:21 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 17:17:11 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VALIDATE_H
# define FT_VALIDATE_H

# include "libft.h"

int		ft_validate_cmd_permisions(t_list *cmd);
void	ft_validate_write_file(char *file);
int		ft_validate_cmd_if_exist(t_list *cmds);
#endif