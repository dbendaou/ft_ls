/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 18:50:12 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 15:48:41 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** LIST_FREE : libère la liste
*/

void		list_free(t_file **begin)
{
	t_file		*tmp;
	t_file		*tmpp;

	tmp = *begin;
	tmpp = tmp->next;
	while (tmp)
	{
		free(tmp);
		tmp = tmpp;
		if (tmpp)
			tmpp = tmpp->next;
	}
	*begin = NULL;
}
