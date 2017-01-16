/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 10:00:01 by hivian            #+#    #+#             */
/*   Updated: 2017/01/13 11:46:23 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void			get_sect_index(t_env *e)
{
	t_section_64	*sect_text;
	size_t			i;

	e->segment = (t_segment_command_64*)e->load_cmd;
	e->section = (t_section_64 *)((char*)e->segment + sizeof(*e->segment));
	i = -1;
	while (++i < e->segment->nsects)
	{
		sect_text = e->section + i;
		if (!ft_strcmp(sect_text->sectname, SECT_TEXT))
		{
			print_t_64(sect_text, e);
			break ;
		}
	}
}

void				handle_64(t_env *e)
{
	size_t			i;

	i = 0;
	e->header = (t_mach_header_64 *)e->ptr;
	e->load_cmd = (void*)e->ptr + sizeof(*e->header);
	while (i < e->header->ncmds)
	{
		e->sym = (t_symtab_command*)e->load_cmd;
		if (e->load_cmd->cmd == LC_SEGMENT_64 && e->opt_t)
			get_sect_index(e);
		e->load_cmd = (void *)e->load_cmd + e->load_cmd->cmdsize;
		i++;
	}
	if (e->opt_h)
		print_h_64(e);
}
