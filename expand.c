/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:08:33 by alirola-          #+#    #+#             */
/*   Updated: 2024/04/11 20:00:59 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_content(t_data *d, char *s)
{
	//char	*status;
	t_env	*aux;

	aux = d->env;
	/* if (ft_strncmp(s, "?", 1) == EXIT_SUCCESS)
	{
		status = ft_itoa(g_status);
		return (status);
	} */
	while (aux)
	{
		if (ft_strncmp(aux->name, s, ft_strlen(s)) == EXIT_SUCCESS)
			return (ft_strdup(aux->content));
		aux = aux->next;
	}
	return (ft_strdup(""));
}

static void	expand_2(t_data *d, int *i, int *flag, char **exp)
{
	if ((!*flag && d->cmds[d->i][d->j] == '~')
		&& ((d->cmds[d->i][d->j - 1] == ' ' && d->cmds[d->i][d->j + 1] == ' ')
		|| (d->cmds[d->i][d->j + 1] == '\0')
		|| (d->cmds[d->i][d->j + 1] == '/')))
	{
		if (d->cmds[d->i][d->j] == '\'')
			*flag = !*flag;
		*exp = gnl_ft_strjoin(*exp, get_env_content(d, "HOME"));
		d->j++;
	}
	else
	{
		*i = d->j;
		while ((d->cmds[d->i][d->j] != '$' || *flag) && d->cmds[d->i][d->j])
		{
			if (d->cmds[d->i][d->j] == '\'')
				*flag = !*flag;
			d->j++;
		}
		*exp = gnl_ft_strjoin(*exp, ft_substr(d->cmds[d->i], *i, d->j - *i));
	}
}

static void	expand_1(t_data *d, int *i, int *flag, char **expand)
{
	char	*tmp;

	if (d->cmds[d->i][d->j] == '$' && !*flag)
	{
		if (d->cmds[d->i][d->j + 1] == '\0' || d->cmds[d->i][d->j + 1] == ' ')
		{
			*expand = gnl_ft_strjoin(*expand, ft_strdup("$"));
			d->j++;
		}
		else
		{
			d->j++;
			*i = d->j;
			while ((d->cmds[d->i][d->j] != ' ' && d->cmds[d->i][d->j] != '$' &&
				d->cmds[d->i][d->j]) && d->cmds[d->i][d->j] != '\''
				&& d->cmds[d->i][d->j] != '\"')
				d->j++;
			tmp = ft_substr(d->cmds[d->i], *i, d->j - *i);
			*expand = gnl_ft_strjoin(*expand, get_env_content(d, tmp));
			free(tmp);
			tmp = NULL;
		}
	}
}

void	expand(t_data *data)
{
	int		i;
	int		flag;
	char	*expand;

	expand = NULL;
	flag = 0;
	while (data->cmds[++data->i])
	{
		data->j = 0;
		i = 0;
		while (data->cmds[data->i][data->j])
		{
			expand_1(data, &i, &flag, &expand);
			expand_2(data, &i, &flag, &expand);
		}
		free(data->cmds[data->i]);
		data->cmds[data->i] = NULL;
		data->cmds[data->i] = ft_strdup(expand);
		free(expand);
		expand = NULL;
	}
	data->i = 0;
}
