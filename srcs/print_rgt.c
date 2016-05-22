/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:30:51 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 18:38:44 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** PRINT_USEX : affiche les droits d'x de l'user
*/

static void	print_usex(t_file *tmp)
{
	if ((IS_UID(tmp->f_mode) == 1) && (IS_USR(tmp->f_mode) == 1))
		ft_putchar('s');
	else if ((!IS_UID(tmp->f_mode)) && IS_USR(tmp->f_mode))
		ft_putchar('x');
	else if (IS_UID(tmp->f_mode) && (!IS_USR(tmp->f_mode)))
		ft_putchar('S');
	else
		ft_putchar('-');
}

/*
** PRINT_GREX : affiche les droits d'x du grp
*/

static void	print_grex(t_file *tmp)
{
	if ((IS_GID(tmp->f_mode) == 1) && (IS_GRP(tmp->f_mode) == 1))
		ft_putchar('s');
	else if ((!IS_GID(tmp->f_mode)) && IS_GRP(tmp->f_mode))
		ft_putchar('x');
	else if (IS_GID(tmp->f_mode) && (!IS_GRP(tmp->f_mode)))
		ft_putchar('S');
	else
		ft_putchar('-');
}

/*
** PRINT_STICK : affiche sticky ou x pour others
*/

static void	print_stick(t_file *tmp)
{
	if ((IS_STK(tmp->f_mode) == 1) && (IS_OTH(tmp->f_mode) == 1))
		ft_putchar('t');
	else if ((!IS_STK(tmp->f_mode)) && IS_OTH(tmp->f_mode))
		ft_putchar('x');
	else if (IS_STK(tmp->f_mode) && (!IS_OTH(tmp->f_mode)))
		ft_putchar('T');
	else
		ft_putchar('-');
}

/*
** PRINT_TYPE : affiche le type
*/

static void	print_type(t_file *tmp)
{
	if (S_ISFIFO(tmp->f_mode))
		ft_putchar('p');
	else if (S_ISCHR(tmp->f_mode))
		ft_putchar('c');
	else if (S_ISDIR(tmp->f_mode))
		ft_putchar('d');
	else if (S_ISBLK(tmp->f_mode))
		ft_putchar('b');
	else if (S_ISLNK(tmp->f_mode))
		ft_putchar('l');
	else if (S_ISSOCK(tmp->f_mode))
		ft_putchar('s');
	else if (S_ISWHT(tmp->f_mode))
		ft_putchar('w');
	else
		ft_putchar('-');
}

/*
** PRINT_RIGHTS : affiche le type et les droits du fichier
*/

void		print_rights(t_file *tmp)
{
	print_type(tmp);
	ft_putchar(((tmp->f_mode | S_IRUSR) == tmp->f_mode) ? 'r' : '-');
	ft_putchar(((tmp->f_mode | S_IWUSR) == tmp->f_mode) ? 'w' : '-');
	print_usex(tmp);
	ft_putchar(((tmp->f_mode | S_IRGRP) == tmp->f_mode) ? 'r' : '-');
	ft_putchar(((tmp->f_mode | S_IWGRP) == tmp->f_mode) ? 'w' : '-');
	print_grex(tmp);
	ft_putchar(((tmp->f_mode | S_IROTH) == tmp->f_mode) ? 'r' : '-');
	ft_putchar(((tmp->f_mode | S_IWOTH) == tmp->f_mode) ? 'w' : '-');
	print_stick(tmp);
	print_bonus(tmp);
	ft_putstr(" ");
}
