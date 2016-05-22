/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openlink.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:30:51 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 18:38:42 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		open_iflink(t_file **current, t_params *params)
{
	struct stat	buf;
	char		buff[1024];
	char		tmpp[1024];
	t_file		*tmp;
	char		*name;

	tmp = *current;
	bzero(buff, 1024);
	ft_strcpy(buff, tmp->f_path);
	name = get_filename(buff);
	bzero(tmpp, 1024);
	readlink(tmp->f_path, tmpp, 1024);
	ft_strcpy(name, tmpp);
	if (lstat(buff, &buf) != 0)
		return (0);
	if (S_ISDIR(buf.st_mode) && (!IS_L(params->prms)))
	{
		bzero(tmp->f_path, 1024);
		ft_strcpy(tmp->f_path, buff);
		return (dir_list(current, params));
	}
	return (0);
}
