/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lprint_oth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:37:21 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 17:45:50 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** TOTAL_PRINT : affiche le total des blocks du dossier
*/

void		total_print(t_file *to_print, t_params *params)
{
	t_file	*tmpp;
	quad_t	total_blk;
	int		test;

	tmpp = to_print->contain;
	total_blk = 0;
	test = 0;
	while (tmpp)
	{
		while (tmpp->f_name[0] == '.' && tmpp->next
			&& (!IS_A(params->prms)))
			tmpp = tmpp->next;
		if (tmpp && is_print(tmpp, params))
		{
			test++;
			total_blk += tmpp->f_blocks;
		}
		tmpp = tmpp->next;
	}
	if (test)
	{
		ft_putstr("total ");
		ft_putnbr((int)total_blk);
		ft_putchar('\n');
	}
}

/*
** PRINT_NBLK : affiche le nb de links
*/

void		print_nblk(t_file *to_print, int max)
{
	int		diff;

	diff = max - ft_intlen((int)to_print->f_nlink);
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
	ft_putnbr((int)to_print->f_nlink);
	ft_putchar(' ');
}

/*
** PRINT_DEVICE : si device : affiche min et maj
*/

void		print_device(t_file *to_print, t_max *max)
{
	int		diff;

	diff = max->m_maj - ft_intlen((int)major(to_print->f_rdev));
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
	ft_putnbr((int)major(to_print->f_rdev));
	ft_putstr(", ");
	diff = max->m_min - ft_intlen((int)minor(to_print->f_rdev));
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
	ft_putnbr((int)minor(to_print->f_rdev));
	ft_putstr(" ");
}

/*
** PRINT_SIZE : affiche size
*/

void		print_size(t_file *to_print, t_max *max)
{
	int		diff;

	if (S_ISBLK(to_print->f_mode) || S_ISCHR(to_print->f_mode))
		return (print_device(to_print, max));
	diff = max->m_sprint - ft_intlen(to_print->f_size);
	while (diff > 0)
	{
		ft_putchar(' ');
		diff--;
	}
	ft_putnbr((int)to_print->f_size);
	ft_putstr(" ");
}

/*
** DATE_PRINTER : tout est dans le nom
*/

void		date_printer(t_file *to_print)
{
	char	date[25];

	ft_bzero(date, 25);
	ft_strcpy(date, ctime(&to_print->f_time.tv_sec));
	if (time(NULL) - (to_print->f_time.tv_sec) > 15778800
		|| time(NULL) < to_print->f_time.tv_sec)
	{
		ft_putnstr(4, 11, date);
		ft_putchar(' ');
		ft_putnstr(20, 24, date);
	}
	else
		ft_putnstr(4, 16, date);
	ft_putstr(" ");
}
