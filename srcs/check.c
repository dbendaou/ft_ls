/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:25:21 by dbendaou          #+#    #+#             */
/*   Updated: 2016/03/30 17:51:53 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_nprint(char *name, t_params *params)
{
	if (IS_A(params->prms))
		return (1);
	else if (name[0] == '.')
		return (0);
	return (1);
}

int		count_dr(t_file *begin)
{
	t_file	*tmp;
	int		i;
	char	*name;

	i = 0;
	tmp = begin;
	while (tmp)
	{
		name = get_filename(tmp->f_path);
		if (S_ISDIR(tmp->f_mode) && (ft_strcmp("..", name) != 0)
			&& (ft_strcmp(name, ".") != 0))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int		first_check(t_file *tmp, t_file *new)
{
	if ((S_ISDIR(tmp->f_mode) && !S_ISDIR(new->f_mode))
		|| (S_ISDIR(tmp->f_mode) && S_ISDIR(new->f_mode)
		&& ft_strcmp(tmp->f_path, new->f_path) > 0)
		|| (!S_ISDIR(tmp->f_mode) && !S_ISDIR(new->f_mode)
		&& ft_strcmp(tmp->f_path, new->f_path) > 0))
		return (1);
	else
		return (0);
}

int		second_check(t_file *tmp, t_file *new)
{
	if ((!S_ISDIR(tmp->next->f_mode) && S_ISDIR(new->f_mode))
		|| (S_ISDIR(tmp->next->f_mode) && S_ISDIR(new->f_mode)
		&& ft_strcmp(tmp->next->f_path, new->f_path) < 0)
		|| ((!S_ISDIR(tmp->next->f_mode) && !S_ISDIR(new->f_mode)
		&& ft_strcmp(tmp->next->f_path, new->f_path) < 0)))
		return (1);
	else
		return (0);
}

int		is_next(t_file *current)
{
	t_file	*tmp;

	tmp = current;
	while (tmp)
	{
		if (tmp->next)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
