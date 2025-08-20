/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:20:32 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/20 13:05:58 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_core.h"
#include "ft_error.h"
#include "ft_parse.h"
#include "ft_settings.h"
#include "ft_utils.h"
#include "ft_validate.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmds;
	int		fd_in;
	int		fd_out;

	if (argc < 5)
		return (EXIT_FAILURE);
	if (!ft_strcmp(argv[1], HERE_DOC))
	{
		ft_open_here_doc(argv[2], argv[argc - 1], &fd_in, &fd_out);
		cmds = ft_parse_args(argc - 4, argv + 3);
	}
	else
	{
		fd_open_files(&fd_in, &fd_out, argv[1], argv[argc - 1]);
		cmds = ft_parse_args(argc - 3, argv + 2);
	}
	if (!cmds)
		return (ft_print_errormsg(ARG_ERROR), EXIT_FAILURE);
	ft_set_progname(cmds, envp);
	ft_validate_cmd_if_exist(cmds, fd_in);
	ft_validate_cmd_permisions(cmds);
	ft_run(cmds, fd_in, fd_out, envp);
	ft_lstclear(&cmds, ft_free_pipe);
	return (EXIT_SUCCESS);
}
