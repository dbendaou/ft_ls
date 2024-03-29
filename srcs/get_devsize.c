/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_devsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:37:11 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 17:09:48 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** MAX_MIN : obtient la len du champs minor si blk ou socket
*/

int		max_min(t_file *to_print, t_params *params)
{
	int		max;
	t_file	*tmp;

	tmp = to_print;
	max = 0;
	while (tmp)
	{
		if (((S_ISBLK(tmp->f_mode)) || (S_ISCHR(tmp->f_mode)))
			&& is_print(tmp, params))
			max = ((int)minor(tmp->f_rdev) > max) ?
				(int)minor(tmp->f_rdev) : max;
		tmp = tmp->next;
	}
	if (max == 0)
		return (0);
	return (ft_intlen(max));
}

/*
** MAX_MAJ : idem avec major
*/

int		max_maj(t_file *to_print, t_params *params)
{
	int		max;
	t_file	*tmp;

	tmp = to_print;
	max = 0;
	while (tmp)
	{
		if (((S_ISBLK(tmp->f_mode)) || (S_ISCHR(tmp->f_mode)))
			&& is_print(tmp, params))
			max = ((int)major(tmp->f_rdev) > max) ?
				(int)major(tmp->f_rdev) : max;
		tmp = tmp->next;
	}
	if (max == 0)
		return (0);
	return (ft_intlen(max));
}
