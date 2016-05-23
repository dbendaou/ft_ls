/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:38:49 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 17:13:07 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	rec1(t_file *tmp, t_params *params, int *i, char ***next)
{
	char	**next_ls;

	print_dname(tmp, params);
	if (IS_L(params->prms))
		total_print(tmp, params);
	(IS_L(params->prms)) ? lprint(tmp->contain, params)
		: printer(tmp->contain, params);
	next_ls = get_nextls(tmp->contain, i, params);
	if (next_ls == NULL && is_next(tmp))
		ft_putchar('\n');
	*next = next_ls;
}

void	rec2(t_file *tmp, t_params *params)
{
	t_file	*dir;

	dir = tmp->next;
	tmp->next = NULL;
	(IS_L(params->prms)) ? lprint(tmp, params) : printer(tmp, params);
	tmp->next = dir;
	dir = NULL;
	if (is_next(tmp))
		ft_putchar('\n');
}

void	recursive(t_file **file, t_params *params, int *i, char ***next)
{
	t_file	*tmp;

	tmp = *file;
	while (tmp)
	{
		if (tmp->contain && tmp->error != 1)
		{
			rec1(tmp, params, i, next);
			list_free(&(tmp->contain));
		}
		else if (tmp->error != 1)
			rec2(tmp, params);
		if (*next)
		{
			ft_putchar('\n');
			params->count = 0;
			ft_ls(*i, *next, params);
			if (is_next(tmp))
				ft_putchar('\n');
		}
		tmp = tmp->next;
	}
	list_free(file);
}

void	l_help(t_file *tmpp, t_file *tmp, t_params *params)
{
	t_max *max;

	print_dname(tmpp, params);
	if (is_error(tmpp->contain))
		total_print(tmpp, params);
	max = get_max(tmpp->contain, params);
	while (tmp)
	{
		if (is_print(tmp, params) && tmp->error != 1)
			line_printer(tmp, max);
		tmp = tmp->next;
	}
	free(max);
}
