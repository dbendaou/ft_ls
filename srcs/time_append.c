/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:30:51 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 19:17:40 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			time_check1(t_file *tmp, t_file *to_add)
{
	if (tmp->f_time.tv_sec > to_add->f_time.tv_sec)
		return (1);
	if ((tmp->f_time.tv_sec == to_add->f_time.tv_sec)
		&& (tmp->f_time.tv_nsec > to_add->f_time.tv_nsec))
		return (1);
	if ((tmp->f_time.tv_sec == to_add->f_time.tv_sec)
		&& (tmp->f_time.tv_nsec == to_add->f_time.tv_nsec)
		&& (ft_strcmp(tmp->f_name, to_add->f_name) < 0))
		return (1);
	else
		return (0);
}

int			time_check2(t_file *tmp, t_file *to_add)
{
	if (tmp->f_time.tv_sec < to_add->f_time.tv_sec)
		return (1);
	if ((tmp->f_time.tv_sec == to_add->f_time.tv_sec)
		&& (tmp->f_time.tv_nsec < to_add->f_time.tv_nsec))
		return (1);
	if ((tmp->f_time.tv_sec == to_add->f_time.tv_sec)
		&& (tmp->f_time.tv_nsec == to_add->f_time.tv_nsec)
		&& (ft_strcmp(tmp->f_name, to_add->f_name) > 0))
		return (1);
	else
		return (0);
}

void		t_app(char *path, t_file **begin, struct dirent *buf, t_params *pr)
{
	t_file	*tmp;
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	tmp = *begin;
	readstat(path, new, pr);
	if (buf)
		ft_strcpy(new->f_name, buf->d_name);
	else
		ft_strcpy(new->f_name, path);
	if (time_check2(tmp, new))
	{
		new->next = tmp;
		*begin = new;
		return ;
	}
	while (tmp->next && time_check1(tmp->next, new))
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
}

void		first_tappend(char *path, t_file **begin, t_params *params)
{
	t_file	*tmp;
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	tmp = *begin;
	readstat(path, new, params);
	ft_strcpy(new->f_name, path);
	if ((S_ISDIR(tmp->f_mode) && !S_ISDIR(new->f_mode))
		|| (S_ISDIR(tmp->f_mode) && S_ISDIR(new->f_mode)
		&& time_check2(tmp, new)) || (!S_ISDIR(tmp->f_mode)
		&& !S_ISDIR(new->f_mode) && time_check2(tmp, new)))
	{
		new->next = tmp;
		*begin = new;
		return ;
	}
	while (tmp->next && ((S_ISDIR(tmp->next->f_mode) && !S_ISDIR(new->f_mode))
		|| (S_ISDIR(tmp->next->f_mode) && S_ISDIR(new->f_mode)
		&& time_check1(tmp->next, new)) || (!S_ISDIR(tmp->next->f_mode)
		&& !S_ISDIR(new->f_mode) && time_check1(tmp->next, new))))
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
}
