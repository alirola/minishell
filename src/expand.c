/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:17:20 by alirola-          #+#    #+#             */
/*   Updated: 2024/04/05 17:16:16 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_env(char **s, t_data *d)
{
	t_env	*aux;
	char	**exp;

	aux = d->env;
	while (aux)
	{
		if (ft_strncmp(s[1], aux->name, ft_strlen(s[1])) == EXIT_SUCCESS)
		{
			exp = ft_split(aux->content, '=');
			d->expand = exp[0];
		}
		else
			aux = aux->next;
	}
	printf("hola\n");
}

void	expand_select(char *s, t_data *d)
{
	int		i;
	//char	*status;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '$') && (s[i + 1] != '$' || s[i + 1] != '?'))
		{
			printf("adios");
			expand_env(ft_split(s, '$'), d);
		}
		/* else if (s[i] == '$' && s[i + 1] == '?')
		{
			status = ft_itoa(g_status);
			return (status);
		} */
		/* else if(s[i] == '$' && s[i + 1] == '$')
			expand_env(ft_split(s, '$$'), d); */
		else
			i++;
	}
}

void	expand_exe(t_data *d, t_parser *node)
{
	int	args;
	int	i;

	i = 0;
	args = 1;
	while (node->full_cmd[args])
	{
		while (node->full_cmd[args][i])
		{
			if (node->full_cmd[args][i] == '$')
			{
				expand_select(node->full_cmd[args], d);
			}
			else
				i++;
		}
	}
	if (ft_strncmp(node->full_cmd[0], "echo\0", 5) == EXIT_SUCCESS)
		echo_exe(&d->expand, 0);
	else
		printf("bash: %s: command not found\n", d->expand);
}
