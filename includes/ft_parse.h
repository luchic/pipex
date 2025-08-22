/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:53:41 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/22 15:25:14 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_H
# define FT_PARSE_H

# include "libft.h"

t_list	*ft_parse_args(int argc, char **argv);
char	**ft_getenv_paths(char **envp);
int		ft_set_progname(t_list *cmds, char **envp);
char	**ft_split_args(char *str, char delim);
char	*ft_default_getenv(void);

char	*ft_copy_until_quote(char *str, char ***args);
char	*ft_copy_until_delim(char *str, char ***args, char delim);
char	*ft_copy_until_double_quote(char *str, char ***args);
int		ft_update_args(char ***args, char *str);

#endif