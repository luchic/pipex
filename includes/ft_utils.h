/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:40:58 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 19:37:52 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "ft_pipe.h"
# include "libft.h"

void	ft_free_pipe(void *cont);
void	ft_free_split(char **split);
void	ft_close_pipe(t_list *cmds);
void	ft_set_pipes(t_list *cmd);

#endif