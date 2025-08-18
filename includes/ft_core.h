/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:14:20 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 17:36:02 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CORE_H
# define FT_CORE_H

# include "libft.h"
# include "ft_pipe.h"

int		ft_run(t_list *cmds, int fd_inline, int fd_outline, char **envp);
void	ft_run_child(t_list *head, t_pipe *cur_process, char **envp);
void	ft_close_pipe(t_list *cmds);
void	ft_set_pipes(t_list *cmd);

#endif