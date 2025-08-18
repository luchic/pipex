/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:53:41 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/18 21:30:27 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_H
# define FT_PARSE_H

# include "libft.h"

t_list	*ft_parse_args(int argc, char **argv);
char	**ft_getenv_paths(char **envp);
int		ft_set_progname(t_list *cmds, char **envp);
char	**ft_split_args(char *str, char delim);
int		ft_get_readfile(char *file);
int		ft_get_writefile(char *file);
char	**ft_merge_qute(char **args, int size, char quote);
char	**ft_default_getenv(void);

#endif