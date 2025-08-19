/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:20:32 by nluchini          #+#    #+#             */
/*   Updated: 2025/08/19 19:04:33 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_core.h"
#include "ft_parse.h"
#include "ft_printf.h"
#include "ft_settings.h"
#include "ft_validate.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmds;
	int		fd_in;
	int		fd_out;

	// envp = NULL;
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
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", PIPEX, ARG_ERROR);
		return (EXIT_FAILURE);
	}
	ft_set_progname(cmds, envp);
	ft_validate_cmd_if_exist(cmds);
	ft_validate_cmd_permisions(cmds);
	ft_run(cmds, fd_in, fd_out, envp);
}
