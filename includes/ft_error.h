/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:54:33 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 17:27:52 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

void	ft_open_pipe_errormsg(void);
void	ft_common_errormsg(void);
void	ft_command_not_found_errormsg(char *cmd);
void	ft_std_errmsg(char *msg);
#endif