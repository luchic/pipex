/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:29:47 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 16:32:18 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPE_H
# define FT_PIPE_H

typedef struct s_pipe
{
	int		to_exec;
	int		fd_inline;
	int		fd_outline;
	int		pid;
	char	*cmdname;
	char	**args;
}			t_pipe;

#endif