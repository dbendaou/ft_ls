/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_devsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:30:51 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 18:38:26 by dbendaou         ###   ########.fr       */
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
** MAX_MAJ : idem ac major
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
