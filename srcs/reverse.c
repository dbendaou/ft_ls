/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:51:48 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 17:10:39 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** REVERSE : inverse une liste simplement chainee
*/

t_file	*reverse(t_file *ptr)
{
	t_file *temp;
	t_file *previous;

	previous = NULL;
	while (ptr != NULL)
	{
		temp = ptr->next;
		ptr->next = previous;
		previous = ptr;
		ptr = temp;
	}
	return (previous);
}

void	rev_help(t_file **to_rev, t_file **begin)
{
	t_file *tmp;
	t_file *fmp;
	t_file *tmpp;

	tmp = *to_rev;
	fmp = tmp->next;
	tmpp = tmp;
	tmp = *begin;
	while (!S_ISDIR(tmp->f_mode) && !S_ISDIR(tmp->next->f_mode))
		tmp = tmp->next;
	if (S_ISDIR(tmp->f_mode))
	{
		tmpp->next = tmpp->next->next;
		fmp->next = *begin;
		*begin = fmp;
	}
	else if (S_ISDIR(tmp->next->f_mode))
	{
		tmpp->next = tmpp->next->next;
		fmp->next = tmp->next;
		tmp->next = fmp;
	}
}

/*
** FIRST_REVERSE : remet fichiers en premier apres reverse au premier appel
*/

void	first_reverse(t_file **to_rev)
{
	t_file	*tmp;

	tmp = *to_rev;
	while (tmp && tmp->next)
	{
		if (S_ISDIR(tmp->f_mode) && !(S_ISDIR(tmp->next->f_mode)))
		{
			rev_help(&tmp, to_rev);
			tmp = *to_rev;
		}
		tmp = tmp->next;
	}
}

/*
** REVERSE_LIST : inverse l'ordre des listes imbriquees
*/

void	reverse_list(t_file **to_rev)
{
	t_file		*tmp;
	t_file		*tmpp;
	static int	i = 0;

	tmp = *to_rev;
	*to_rev = reverse(tmp);
	tmp = *to_rev;
	while (tmp)
	{
		if (tmp->contain)
		{
			tmpp = reverse(tmp->contain);
			tmp->contain = tmpp;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		first_reverse(to_rev);
	i = 4;
}
