/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:43:25 by nluchini          #+#    #+#             */
/*   Updated: 2025/07/29 13:32:10 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/**
 * @brief The replica of the printf function from the C standard library.
 * This function formats and prints a string to the standard output.  
 * @param  format: The format string that specifies how to format the output. 
 * @retval The number of characters printed. -1 if an error occurs.
 */
int	ft_printf(const char *format, ...);

#endif