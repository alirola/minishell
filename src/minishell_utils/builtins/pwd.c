/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:41:03 by alirola-          #+#    #+#             */
/*   Updated: 2024/04/09 16:46:59 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_exe(int fd)
{
	char	actual_dir[500];

	getcwd(actual_dir, 500);
	ft_printf(fd, "%s\n", actual_dir);
}