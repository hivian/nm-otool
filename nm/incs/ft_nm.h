/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 15:00:44 by hivian            #+#    #+#             */
/*   Updated: 2017/01/16 09:54:36 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "../../libft/incs/libft.h"
# include <stdio.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdbool.h>

# define N_LSYM_INDEX 14

typedef struct stat					t_stat;
typedef struct load_command			t_load_command;
typedef struct symtab_command		t_symtab_command;
typedef struct process_flags		t_process_flags;

typedef struct nlist_64				t_nlist64;
typedef struct mach_header_64		t_mach_header_64;
typedef struct segment_command_64	t_segment_command_64;
typedef struct section_64			t_section_64;

typedef struct nlist				t_nlist;
typedef struct mach_header			t_mach_header;
typedef struct segment_command		t_segment_command;
typedef struct section				t_section;

typedef struct				s_env
{
	void					*ptr;
	unsigned int			magic_nb;
	t_load_command			*load_cmd;
	t_symtab_command		*sym;
	t_process_flags			*p_flags;
	t_nlist64				*symbols;
	t_mach_header_64		*header;
	t_segment_command_64	*segment;
	t_section_64			*section;
	t_nlist					*symbols_32;
	t_mach_header			*header_32;
	t_segment_command		*seg_32;
	t_section				*section_32;
	char					*str_table;
	int						nb_syms;
	int						sym_off;
	int						str_off;
	int						text_nsect;
	int						data_nsect;
	int						bss_nsect;
	char					***output_arr;
	int						n_type;
	long long int			n_value;
	int						n_sect;
	char					*str_symbol;
	bool					is_lsym;
	bool					opt_j;
	bool					opt_p;
	bool					opt_u;
	bool					opt_big_u;
	bool					is_arg;
}							t_env;

void						nm(t_env *e);
int							print_error(char *msg);
void						handle_64(t_env *e);
void						handle_32(t_env *e);
void						print_output(t_env *e);
void						sort_alpha(t_env *e);
long long int				llatoi(const char *str);
void						free_array(t_env *e);

#endif
