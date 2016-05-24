/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:30:21 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 18:47:40 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** MAX_LINK : obtiens le nombres maximum de ln-s
*/

static int		max_link(t_file *to_print, t_params *params)
{
	t_file	*tmp;
	int		max;

	max = 0;
	tmp = to_print;
	while (tmp)
	{
		if (tmp->f_nlink > max && is_print(tmp, params))
			max = tmp->f_nlink;
		tmp = tmp->next;
	}
	return (ft_intlen((int)max));
}

/*
**MAX_USR : obtient la len max du champs user
*/

static int		max_usr(t_file *to_print, t_params *params)
{
	t_file			*tmp;
	int				max;
	int				size;
	struct passwd	*pwd;

	max = 0;
	size = 0;
	tmp = to_print;
	while (tmp)
	{
		if (is_print(tmp, params))
		{
			pwd = getpwuid(tmp->f_uid);
			if (!pwd)
				size = ft_intlen(tmp->f_uid);
			else
				size = ft_strlen(pwd->pw_name);
			if (size > max)
				max = size;
		}
		tmp = tmp->next;
	}
	return (max);
}

/*
** MAX_GRP : obtient la len max du chmps grp
*/

static int		max_grp(t_file *to_print, t_params *params)
{
	t_file			*tmp;
	int				max;
	int				size;
	struct group	*grp;

	max = 0;
	tmp = to_print;
	size = 0;
	while (tmp)
	{
		if (is_print(tmp, params))
		{
			grp = getgrgid(tmp->f_gid);
			if (!grp)
				size = ft_intlen(tmp->f_gid);
			else
				size = ft_strlen(grp->gr_name);
			if (size > max)
				max = size;
		}
		tmp = tmp->next;
	}
	return (max);
}

/*
** MAX_SIZE : obrient la len max du champs size
*/

static int		max_size(t_file *to_print, t_params *params)
{
	t_file	*tmp;
	int		max;

	max = 0;
	tmp = to_print;
	while (tmp)
	{
		if ((tmp->f_size > max) && is_print(tmp, params))
			max = tmp->f_size;
		tmp = tmp->next;
	}
	return (ft_intlen(max));
}

/*
** GET_MAX : création de la struct des size max des differents infos
*/

t_max			*get_max(t_file *to_print, t_params *params)
{
	t_max	*max;

	max = (t_max *)malloc(sizeof(t_max));
	max->m_link = max_link(to_print, params);
	max->m_usr = max_usr(to_print, params);
	max->m_grp = max_grp(to_print, params);
	max->m_size = max_size(to_print, params);
	max->m_min = max_min(to_print, params);
	max->m_maj = max_maj(to_print, params);
	if ((max->m_min == 0) && (max->m_maj == 0))
		max->m_sprint = max->m_size;
	else if ((max->m_min + max->m_maj + 2) > max->m_size)
		max->m_sprint = max->m_min + max->m_maj + 2;
	else
		max->m_sprint = max->m_size;
	return (max);
}
