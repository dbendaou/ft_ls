/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:30:51 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 18:38:34 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** PRINT_NAME : affiche le nm du file en cours
*/

void		print_name(t_file *to_print)
{
	char	buf[1024];

	if (S_ISLNK(to_print->f_mode))
	{
		bzero(buf, 1024);
		readlink(to_print->f_path, buf, 1024);
		ft_putstr(to_print->f_name);
		ft_putstr(" -> ");
		ft_putstr(buf);
	}
	else
		ft_putstr(to_print->f_name);
}

/*
** PRINT_DNAME : affichage du nom du dossier si > 1
*/

void		print_dname(t_file *to_print, t_params *params)
{
	if (params->count > 1 || IS_RC(params->prms))
	{
		ft_putstr(to_print->f_path);
		ft_putstr(":\n");
	}
}

/*
** LINE_PRINTER : affichage dune ligne avec -l
*/

void		line_printer(t_file *tmp, t_max *max)
{
	print_rights(tmp);
	print_nblk(tmp, max->m_link);
	print_usr(tmp, max->m_usr);
	print_grp(tmp, max->m_grp);
	print_size(tmp, max);
	date_printer(tmp);
	print_name(tmp);
	ft_putchar('\n');
}

void		print_bonus(t_file *tmp)
{
	char	buf[512];
	int		ret;
	acl_t	acl;

	bzero(buf, 512);
	ret = listxattr(tmp->f_path, buf, 512, XATTR_NOFOLLOW);
	if (ret > 0)
		ft_putchar('@');
	else if ((acl = acl_get_file(tmp->f_path, ACL_TYPE_EXTENDED)))
	{
		ft_putchar('+');
		acl_free(acl);
	}
	else
		ft_putchar(' ');
}

/*
** LPRINT : gestion de l'affiche avec -l
*/

void		lprint(t_file *to_print, t_params *params)
{
	t_file	*tmp;
	t_file	*tmpp;
	t_max	*maxx;

	tmpp = to_print;
	maxx = NULL;
	maxx = get_max(tmpp, params);
	while (tmpp)
	{
		if (tmpp->error == 1)
			;
		else if ((tmp = tmpp->contain) != NULL)
			l_help(tmpp, tmp, params);
		else if ((!tmpp->contain) && is_print(tmpp, params))
			line_printer(tmpp, maxx);
		if (tmpp->next && tmpp->next->contain != NULL)
			ft_putchar('\n');
		tmpp = tmpp->next;
	}
	if (maxx)
		free(maxx);
}
