/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:14:20 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 16:36:11 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CORE_H
# define FT_CORE_H

# include "ft_pipe.h"
# include "libft.h"

int		ft_run(t_list *cmds, int fd_inline, int fd_outline, char **envp);
void	ft_run_child(t_list *head, t_pipe *cur_process, char **envp);
void	fd_open_files(int *fd_in, int *fd_out, char *input_file,
			char *output_file);
void	ft_open_here_doc(char *delimiter, char *output_file, int *fd_in,
			int *fd_out);

#endif