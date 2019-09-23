/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/23 20:56:44 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"

#define REQUEST_REGISTER	game->carriages->current_register
#define CARRIAGE_LOCATION	game->carriages->current_location
#define DYNAMIC_SIZE_DIR	4 - game->carriages->current_command->dir_size

typedef enum				byte_blocks_e
{
	BINARY_LABEL			= SIZE_BINARY_LABEL,
	NAME					= BINARY_LABEL + PROG_NAME_LENGTH,
	CODE_SIZE				= NAME + NULL_SEPARATOR + SIZE_VARIABLE,
	COMMENT					= CODE_SIZE + COMMENT_LENGTH,
	CODE					= COMMENT + NULL_SEPARATOR + CHAMP_MAX_SIZE
}							byte_blocks_t;

#define	R1					1
#define	R2					2
#define	R3					3
#define	R4					4
#define	R5					5
#define	R6					6
#define	R7					7
#define	R8					8
#define	R9					9
#define	R10					10
#define	R11					11
#define	R12					12
#define	R13					13
#define	R14					14
#define	R15					15
#define	R16					16

#define	COMMAND_AMOUNT		16
#define DIRECTION_SIZE		4
#define SHORT_DIR_SIZE		2
#define OVERSTEP_NAME		1
#define REGISTR_SIZE		1
#define TO_FIRST_ARG		1
#define ERROR				-335

#define PUT_WAITING_TIME(x)	(x << 48)
#define PUT_DIR_SIZE(x)		(x << 40)
#define PUT_ID(x)			(x << 32)
#define PUT_FIRST_ARG(x)	(x << 31)
#define PUT_SECOND_ARG(x)	(x << 30)
#define PUT_THIRD_ARG(x)	(x << 29)
#define PUT_CHANGE_CARRY(x)	(x << 28)
#define PUT_AVAI_TYPES(x)	(x << 27)

#define GET_WAITING_TIME(x) (x >> 48)
#define GET_DIR_SIZE(x)		(x << 16) >> 56
#define GET_ID(x)			(x << 24) >> 56
#define GET_FIRST_ARG(x)	(x << 32) >> 63
#define GET_SECOND_ARG(x)	(x << 33) >> 63
#define GET_THIRD_ARG(x)	(x << 34) >> 63
#define GET_CHANGE_CARRY(x)	(x << 35) >> 63
#define GET_AVAI_TYPES(x)	(x << 36) >> 63

/*
**	-------------------------
**	Defines for error_catcher
*/

#define MEMORY_ALLOC_ERROR	1
#define NOT_VALID_ARG		2
#define OPEN_FILE_ERROR		3
#define READ_FILE_ERROR		4
#define INCORRECT_BINARY	5
#define TOO_BIG_SIZE		6
#define CHEAT_DETECT		7
#define ARGS_AMOUN_ERROR	8
#define INVALID_PLAYERS		9

#define DESTRUCTOR			"Destructor"
#define GAME				"Game"
#define KEYS				"Keys"
#define PLAYER				"Player"
#define CARRIAGE			"Carriage"
#define ARENA				"Arena"
#define COMMAND				"Command"
#define INIT				"Initialization"

/*
** ---------------------------
*/

#define TRUE				1
#define FALSE				0
#define CARRIAGE_ID_STEP	10

#define LIVE				0x01
#define LD					0x02
#define ST					0x03
#define ADD					0x04
#define SUB					0x05
#define AND					0x06
#define OR					0x07
#define XOR					0x08
#define ZJMP				0x09
#define LDI					0x0a
#define STI					0x0b
#define FORK				0x0c
#define LLD					0x0d
#define LLDI				0x0e
#define LFORK				0x0f
#define AFF					0x10

#define FIRST_ARG			game->carriages->current_command->first_arg
#define SECOND_ARG			game->carriages->current_command->second_arg
#define THIRD_ARG			game->carriages->current_command->third_arg

#define ONE_MORE_LIVE		1
#define READING_MODE		1
#define WRITING_MODE		2

typedef struct	corewar_s corewar_t;

typedef struct				player_s
{
	int						id;
	int						code_size;
	int						carriage_id;
	int						binary_label;
	unsigned char			*code;
	unsigned char			*name;
	unsigned char			*source;
	unsigned char			*comment;
	struct player_s			*next;
	struct player_s			*prev;
}							player_t;

typedef struct				command_s
{
	unsigned int			id;
	unsigned int			first_arg;
	unsigned int			second_arg;
	unsigned int			third_arg;
	unsigned int			dir_size;
	unsigned int			change_carry;
	unsigned int			waiting_time;
	unsigned int			availability_types;
	void					(*function)(corewar_t *);
}							command_t;

typedef struct				carriage_s
{
	int						id;
	int						next_step;
	int						tmp_value;
	int						carry_flag;
	int						waiting_time;
	int						last_live_loop;				// -> lst-live
	int						current_location;
	int						save_point;
	int						current_register;
	unsigned char			*common_buf;
	unsigned char			*value_buf1;
	unsigned char			*value_buf2;
	unsigned char			*value_buf3;
	unsigned char			*address_buf;
	unsigned char			*registers;
	struct carriage_s		*next;
	struct carriage_s		*prev;
	command_t				*current_command;
	player_t				*owner;
}							carriage_t;

typedef struct				arena_s
{
	player_t				*last_survivor;
	unsigned char			*field;
	unsigned long long		loop_amount;
	int						check_amount;
	int						cycle_to_die;
	int						live_amount_in_ctd;
}							arena_t;

typedef struct				destructor_s
{
	int						keys_detect;
	int						self_detect;
	int						game_detect;
	int						arena_detect;
	int						players_detect;
	int						commands_detect;
	int						carriages_detect;
}							destructor_t;

typedef struct				key_s
{
	unsigned int			custom_id;
	unsigned int			concurance_cpu;
	unsigned int			concurance_gpu;
	unsigned int			visualizator;
	unsigned int			extended_param;
}							key_t;

typedef struct				corewar_s
{
	int						players_amount;
	int						carriages_amount;
	int						commands_amount;
	int						pause;
	key_t					*keys;
	arena_t					*arena;
	player_t				*players;
	command_t				*commands[COMMAND_AMOUNT + 1];
	carriage_t				*carriages;
	destructor_t			*destructor;
}							corewar_t;

void						validate_player				(player_t *player);
void						build_player				(player_t *player);
void						arrange_units				(corewar_t *game);
void						introduce_players			(corewar_t *game);
void						here_we_go					(corewar_t *game);
void						print_arena					(corewar_t *game);
void						cwConversetionIntToBytes	(unsigned char *buffer, int *from, int bias);
void						cwConversetionBytesToInt	(unsigned char *buffer, int *dest, int bias);
void						cwReadFromRegToBuf			(unsigned char *buffer, unsigned char *registers, int reg_num, int bias);
void						cwReadFromArenaToBuf		(unsigned char *buffer, unsigned char *field, int data_location, int bias);
void						cwWriteFromBufToReg			(unsigned char *buffer, unsigned char *registers, int reg_num, int bias);
void						cwWriteFromBufToArena		(unsigned char *buffer, unsigned char *field, int data_location, int bias);
void						check_carry					(unsigned char *buffer, int *carry);
void						live_exec					(corewar_t *game);
void						ld_exec						(corewar_t *game);
void						st_exec						(corewar_t *game);
void						add_exec					(corewar_t *game);
void						sub_exec					(corewar_t *game);
void						and_exec					(corewar_t *game);
void						or_exec						(corewar_t *game);
void						xor_exec					(corewar_t *game);
void						zjmp_exec					(corewar_t *game);
void						ldi_exec					(corewar_t *game);
void						sti_exec					(corewar_t *game);
void						fork_exec					(corewar_t *game);
void						lld_exec					(corewar_t *game);
void						lldi_exec					(corewar_t *game);
void						lfork_exec					(corewar_t *game);
void						aff_exec					(corewar_t *game);
void						error_catcher				(int error_code, const char *section);
void						initialization_players		(corewar_t *game, char **argv, int argc);
void						initialization_carriages	(corewar_t *game);
void						initialization_arena		(corewar_t *game);
void						initialization_commands		(corewar_t *game);

#endif