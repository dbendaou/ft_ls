/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:30:51 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 15:53:07 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** DIR_LIST : Lecture des éléments du dossier pour la liste
*/

int		dir_list(t_file **current, t_params *params)
{
	DIR				*dir;
	t_file			*tmp;
	struct dirent	*buf;
	t_file			*begin;
	char			*tmpath;

	tmp = *current;
	begin = (t_file *)malloc(sizeof(t_file));
	ft_bzero(begin->f_path, 1024);
	begin->next = NULL;
	if ((dir = opendir(tmp->f_path)) == NULL)
	{
		stat_error(get_filename(tmp->f_path), tmp);
		list_free(&begin);
		return (0);
	}
	while ((buf = readdir(dir)))
	{
		tmpath = get_filepath((*current)->f_path, buf);
		get_l(tmpath, &begin, buf, params);
		ft_strdel(&tmpath);
	}
	(*current)->contain = begin;
	closedir(dir);
	return (1);
}

/*
** GET_FILE : Creation du premier maillon de
**	la chaine et lecture des arguments envoyés
*/

t_file	*get_file(int ac, char **av, t_params *params)
{
	t_file	*begin;
	int		i;

	i = 0;
	begin = (t_file *)malloc(sizeof(t_file));
	ft_bzero(begin->f_path, 1024);
	begin->next = NULL;
	if (ft_strstr(av[0], "ft_ls"))
		i++;
	while (i < ac)
	{
		if (av[i][0] != '-' || IS_NOPRM(params->prms))
		{
			if (ft_strcmp(av[i], "--") != 0)
			{
				params->count++;
				get_l(av[i], &begin, NULL, params);
			}
		}
		i++;
	}
	if (params->count == 0)
		return (open_current(params, &begin));
	return (begin);
}

/*
** OPEN_IFDIR : Ouvre et lit les dossiers, si le fichier en est un
*/

int		open_ifdir(t_file **begin, t_params *params)
{
	t_file		*tmp;
	int			ret;
	static int	test;

	ret = 0;
	tmp = *begin;
	test = 0;
	while (tmp)
	{
		if (S_ISDIR(tmp->f_mode) || ((tmp->f_mode & S_IFDIR) == S_IFDIR))
		{
			ret = (dir_list(&tmp, params) > 0) ? ret + 1 : ret;
		}
		else if (S_ISLNK(tmp->f_mode) && (test == 0))
		{
			ret = (open_iflink(&tmp, params) > 0) ? ret + 1 : ret;
		}
		tmp = tmp->next;
	}
	test = 4;
	return (ret);
}

/*
** GET_LIST : Pour chaque argument path, on lit les stats
**	et rajoute un maillon a la liste
**	Si buf est nul = premier appel, ensuite buf non nul
**	et f_name rempli pour printer
*/

void	get_l(char *path, t_file **begin, struct dirent *buf, t_params *pr)
{
	t_file	*tmp;

	tmp = *begin;
	if (ft_strlen(tmp->f_path) == 0)
	{
		readstat(path, *begin, pr);
		if (buf != NULL)
			ft_strcpy(tmp->f_name, buf->d_name);
		else
			ft_strcpy(tmp->f_name, path);
		return ;
	}
	else if (buf == NULL && IS_T(pr->prms))
		first_tappend(path, begin, pr);
	else if (IS_T(pr->prms))
		t_app(path, begin, buf, pr);
	else if (buf == NULL)
		first_append(path, begin, pr);
	else
		classic_append(path, begin, pr);
}

/*
** OPEN_CURRENT : ouverture du dossier courant si aucun path specifié
*/

t_file	*open_current(t_params *params, t_file **begin)
{
	params->count++;
	get_l(".", begin, NULL, params);
	return (*begin);
}
