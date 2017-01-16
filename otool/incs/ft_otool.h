/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 09:42:21 by hivian            #+#    #+#             */
/*   Updated: 2017/01/13 14:46:57 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "../../libft/incs/libft.h"
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdbool.h>

typedef struct stat					t_stat;
typedef struct load_command			t_load_command;
typedef struct symtab_command		t_symtab_command;
typedef struct process_flags		t_process_flags;

typedef struct mach_header_64		t_mach_header_64;
typedef struct segment_command_64	t_segment_command_64;
typedef struct section_64			t_section_64;

typedef struct mach_header			t_mach_header;
typedef struct segment_command		t_segment_command;
typedef struct section				t_section;

typedef struct				s_env
{
	char					*ptr;
	unsigned int			magic_nb;
	t_load_command			*load_cmd;
	t_symtab_command		*sym;
	t_process_flags			*p_flags;
	t_mach_header_64		*header;
	t_segment_command_64	*segment;
	t_section_64			*section;
	t_mach_header			*header_32;
	t_segment_command		*segment_32;
	t_section				*section_32;
	bool					opt_h;
	bool					opt_t;
	bool					is_arg;
}							t_env;

int							print_error(char *msg);
void						otool(t_env *e);
void						handle_64(t_env *e);
void						handle_32(t_env *e);
void						print_t_64(t_section_64 *sect_text, t_env *e);
void						print_h_64(t_env *e);
void						print_t_32(t_section *sect_text, t_env *e);
void						print_h_32(t_env *e);

#endif
