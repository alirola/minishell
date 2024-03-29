/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:43:49 by alirola-          #+#    #+#             */
/*   Updated: 2024/03/29 16:05:36 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_cmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

static t_env	*get_first(t_data *data)
{
	t_env	*first;
	t_env	*aux;
	int		i;

	i = 1;
	aux = data->env;
	first = data->env;
	while (aux)
	{
		if (export_cmp(first->name, aux->name) < 0 && aux->index == 0)
			first = aux;
		aux = aux->next;
	}
	return (first);
}

void restart_index(t_data *data)
{
	t_env	*aux;

	aux = data->env;
	while (aux)
	{
		aux->index = 0;
		aux = aux->next;
	}
}

void	set_index(t_data *data)
{
	int		index;
	t_env	*first;
	t_env	*aux;

	index = 1;
	first = data->env;
	while (index <= env_size(data->env))
	{
		aux = data->env;
		while (aux)
		{
			if (exportcmp(first->name, aux->name) > 0 && aux->index == 0)
				first = aux;
			aux = aux->next;
		}
		first->index = index;
		first = get_first(data);
		index++;
	}
}

/* static void	export_exe_null(t_data *data, char *s, char **tmp)
{
	
} */

void	export_exe(t_data *data, char **s, int index)
{
	t_env	*aux;

	restart_index(data);
	set_index(data);
	aux = data->env;
	if (s[1])
		export_exe_null(data, s[1], NULL);
	else if (s[1] == NULL)
	{
		while (aux)
		{
			if (aux->index == index)
			{
				if (ft_strncmp(aux->content, "\"\"\0, 3") == EXIT_SUCCESS)
					printf("declare -x %s=%s\n", aux->name, aux->content);
				else
					printf("declare -x %s=\"%s\"\n", aux->name, aux->content);
				aux = data->env;
				index++;
			}
			else if (aux->index != index)
				aux = aux->next;
		}
	}
	//g_status = 0;
}