/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lprint_gu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:30:51 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 18:38:38 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** PRINT_NBUID : affiche luid si user inconnu
*/

void		print_nbuid(t_file *to_print, int max)
{
	int		diff;

	diff = max - ft_intlen(to_print->f_uid);
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
	ft_putnbr((int)to_print->f_uid);
	ft_putstr(" ");
}

/*
** PRINT_USR : affiche le champs user
*/

void		print_usr(t_file *to_print, int max)
{
	struct passwd	*pwd;
	int				diff;

	pwd = getpwuid(to_print->f_uid);
	if (!pwd)
		return (print_nbuid(to_print, max));
	diff = max - ft_strlen(pwd->pw_name);
	ft_putstr(pwd->pw_name);
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
	ft_putstr("  ");
}

/*
** PRINT_NBGID : affiche gid si grp inconnu
*/

void		print_nbgid(t_file *to_print, int max)
{
	int		diff;

	diff = max - ft_intlen((int)to_print->f_gid);
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
	ft_putnbr((int)to_print->f_gid);
	ft_putstr(" ");
}

/*
** PRINT_GRP : affiche le chps grp
*/

void		print_grp(t_file *to_print, int max)
{
	struct group	*grp;
	int				diff;

	grp = getgrgid(to_print->f_gid);
	if (!grp)
		return (print_nbgid(to_print, max));
	diff = max - ft_strlen(grp->gr_name);
	ft_putstr(grp->gr_name);
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
	ft_putstr("  ");
}
