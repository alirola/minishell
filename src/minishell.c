/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:29:34 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/28 16:35:43 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_leaks(void)
{
	system("leaks -q minishell");
}atexit(ft_leaks); */

static void	init_struct(t_data *data)
{
	data->line = NULL;
	data->path = NULL;
}

int	input(t_data *data)
{
	char *s;
	
	s = "PATH";

	split_path(data);
	split_cmds(data);
	if (ft_strncmp(data->cmds[0], "pwd\0", 4) == EXIT_SUCCESS)
		pwd_exe();
	if (ft_strncmp(data->cmds[0], "env\0", 4) == EXIT_SUCCESS)
		env_exe(data);
	if (ft_strncmp(data->cmds[0], "unset\0", 6) == EXIT_SUCCESS)
		unset_exe(data, data->cmds[1]);
	if (ft_strncmp(data->cmds[0], "cd\0", 3) == EXIT_SUCCESS)
		cd_exe(data, &s, 0);
	/* if (ft_strncmp(data->cmds[0], "exit\0", 5) == EXIT_SUCCESS)
		exit_exe(data); */
	 /* if (!ft_strncmp(data->cmds[0], "cd\0", 7))
	 {
	 	if (cd_exe(data, &s, 0) == EXIT_FAILURE)
	 		return(EXIT_FAILURE);
	 	return (EXIT_SUCCESS);
	 } */
	return (EXIT_SUCCESS);
}

int	minishell(t_data *data, char **env)
{
	piti_shell();
	cigarrette();
	get_env (data, env);
	while (69)
	{
		//hacer minitalk;
		if (prompt(data) == 1)
			exit(EXIT_FAILURE);
		if (ft_strncmp(data->line, "\0", 1) >= 1)
			add_history(data->line);
		if (input(data) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc > 1)
		exit (EXIT_FAILURE);
	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit (EXIT_FAILURE);
	init_struct(data);
	if (minishell(data, env) == EXIT_FAILURE)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
