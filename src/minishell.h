/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:21:29 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/03/21 13:42:08 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libftc/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>

typedef struct s_env
{
	char			*name;
	char			*content;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char	*line;
	char	**path;
	t_env	*env;
	char	**cmds;
	char	*tmp;
	int		path_flag;
}	t_data;

int		main(int argc, char **argv, char **env);
int		prompt(t_data *data);
void	piti_shell(void);
void	cigarrette(void);
int		split_path(t_data *data);
void	get_env(t_data *data, char **env);
int		split_cmds(t_data *data);
void	pwd_exe(void);
void	env_exe(t_data *data);
void	cd_exe(t_data *d, char **s, int flag);
void	unset_exe(t_data *data, char *name);
void	check_path(t_data *data);
int		exit_exe(t_data *data, /*nodo*/);
void	free_path(t_data *data);


#endif
