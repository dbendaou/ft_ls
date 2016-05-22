/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:27:14 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 18:32:15 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** READSTAT : Recuperation des stats d'un fichier
*/

int		readstat(char *path, t_file *file, t_params *params)
{
	struct stat	buf;

	if (lstat(path, &buf) != 0)
	{
		file->error = 1;
		if (is_nprint(get_filename(path), params))
			else_error(get_filename(path));
		return (0);
	}
	file->error = 0;
	(path[ft_strlen(path) - 1] == '/' && ft_strlen(path) > 1) ?
		ft_strncpy(file->f_path, path, ft_strlen(path) - 1)
		: ft_strcpy(file->f_path, path);
	bzero(file->f_name, 1024);
	file->f_mode = buf.st_mode;
	file->f_nlink = buf.st_nlink;
	file->f_uid = buf.st_uid;
	file->f_gid = buf.st_gid;
	file->f_rdev = buf.st_rdev;
	file->f_size = buf.st_size;
	file->f_blocks = buf.st_blocks;
	file->f_time = buf.st_mtimespec;
	file->contain = NULL;
	return (1);
}

/*
** CLASSIC_APPEND : Ajout d'un fichier a la liste selon l'ordre lexico
*/

void	c_app(char *path, t_file **begin, t_params *params)
{
	t_file	*tmp;
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	readstat(path, new, params);
	if (ft_strrchr(path, '/'))
		ft_strcpy(new->f_name, ft_strrchr(path, '/') + 1);
	else
		ft_strcpy(new->f_name, path);
	tmp = (*begin);
	if (ft_strcmp(tmp->f_path, new->f_path) > 0)
	{
		new->next = tmp;
		*begin = new;
		return ;
	}
	while (tmp->next && ft_strcmp(tmp->next->f_path, new->f_path) < 0)
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
}

/*
** FIRST_APPEND : Ajout d'un fichier a la liste au premier appel de la fonction,
** ordonne fichiers/dossiers puis lexico
*/

void	first_append(char *path, t_file **begin, t_params *params)
{
	t_file	*tmp;
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	readstat(path, new, params);
	tmp = (*begin);
	ft_strcpy(new->f_name, path);
	if (first_check(tmp, new))
	{
		new->next = tmp;
		*begin = new;
		return ;
	}
	while (tmp->next && second_check(tmp, new))
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
}
