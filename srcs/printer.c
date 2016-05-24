/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 19:30:01 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 17:11:01 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** IS_PRINT : est-il affichable
*/

int		is_print(t_file *tmp, t_params *params)
{
	char *name;

	name = get_filename(tmp->f_path);
	if (IS_A(params->prms))
		return (1);
	else if (name[0] == '.')
		return (0);
	return (1);
}

/*
** SIMPLE_PRINT : Affichage simple des fichiers
*/

int		is_error(t_file *begin)
{
	t_file *tmp;

	tmp = begin;
	while (tmp)
	{
		if (tmp->error == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
** SIMPLE_PRINT : affichage simple des fichiers
*/

void	simple_print(t_file *begin, t_params *params)
{
	t_file	*tmp;
	t_file	*dir;

	tmp = begin;
	while (tmp)
	{
		if (tmp->error == 1)
			;
		else if ((dir = tmp->contain) && is_error(dir))
		{
			print_dname(tmp, params);
			while (dir)
			{
				if (is_print(dir, params))
					ft_putendl(dir->f_name);
				dir = dir->next;
			}
		}
		else if (is_error(tmp) && is_print(tmp, params))
			(tmp->f_name[0] != 0) ? ft_putendl(tmp->f_name)
				: ft_putendl(tmp->f_path);
		if (tmp->next && (tmp->next->contain != NULL))
			ft_putchar('\n');
		tmp = tmp->next;
	}
}

/*
** PRINTER : Selection de l'affichage en fonction des parametres
*/

void	printer(t_file *begin, t_params *params)
{
	if (IS_L(params->prms))
	{
		lprint(begin, params);
	}
	else
		simple_print(begin, params);
}
