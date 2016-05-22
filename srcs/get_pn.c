/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:30:51 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 18:38:30 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_filename(char *path)
{
	char *tmp;

	if ((tmp = ft_strrchr(path, '/')))
		return (tmp + 1);
	else
		return (path);
}

char	*get_filepath(char *current, struct dirent *buf)
{
	char	*path;
	char	*tmpath;

	if (current[ft_strlen(current) - 1] == '/')
		path = ft_strjoin(current, buf->d_name);
	else
	{
		tmpath = ft_strjoin("/", buf->d_name);
		path = ft_strjoin(current, tmpath);
		ft_strdel(&tmpath);
	}
	return (path);
}
