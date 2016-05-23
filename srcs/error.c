/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 18:42:53 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 15:48:15 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Gestion des erreures
*/

void	arg_error(char arg)
{
	ft_putstr_fd("ft_ls: illegal option: -", 2);
	ft_putchar_fd(arg, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage = ft_ls [-Ralrt] [file ...]", 2);
}

void	else_error(char *path)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(path);
}

void	stat_error(char *path, t_file *tmp)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(path);
	tmp->error = 1;
}
