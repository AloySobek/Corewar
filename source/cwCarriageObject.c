/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwCarriageObject.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:57:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/24 16:18:17 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void cwCopyReg(carriage_t *pCarriageInstance, carriage_t *pCopyingCarriage)
{
	int		iter;

	iter = 0;
	while (iter < CW_REG_SIZE * CW_REG_NUMBER)
	{
		pCopyingCarriage->pRegisters[iter] = pCarriageInstance->pRegisters[iter];
		++iter;
	}
}

static void	cwWriteOwnerIdToReg(carriage_t *pSelfCarriage)
{
	int iter;

	iter = 0;
	while (iter < CW_REG_SIZE)
	{
		pSelfCarriage->pRegisters[iter] = (-pSelfCarriage->pOwnerCarriage->id << (iter * 8)) >> 24;
		++iter;
	}
}

static void	cwCheckCarry(carriage_t *pCarriageInstance)
{
	int iter;

	char test = '1';
//	ft_printf("Checking carry...\n");
	//while (test != 'e')
	//	scanf("%c", &test);
	iter = (pCarriageInstance->currentRegister) * CW_REG_SIZE;
	while (iter < (pCarriageInstance->currentRegister + 1) * CW_REG_SIZE)
	{
		if (pCarriageInstance->pRegisters[iter] != 0)
		{
			pCarriageInstance->carry = 0;
//			ft_printf("Res: %d\n", pCarriageInstance->carry);
			return ;
		}
		++iter;
	}
	pCarriageInstance->carry = 1;
//	ft_printf("Res: %d\n", pCarriageInstance->carry);
}

static void	cwConversionValueToBytes(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, int type)
{
	ft_memset(pBufferObj->pData, 0, CW_REG_SIZE);
	while (type < CW_REG_SIZE)
	{
		pBufferObj->pData[type] = (pBufferObj->sTypes.intValue << (type * 8)) >> 24;
		++type;
	}
}

static void	cwConversionBytesToValue(carriage_t *pCarraigeInstance, buffer_t *pBufferObj, int type)
{
	pBufferObj->sTypes.intValue = 0;
	while (type < CW_REG_SIZE)
	{
		pBufferObj->sTypes.intValue |= pBufferObj->pData[type] << ((3 - type) * 8);
		++type;
	}
}

void		cwWriteOperation(carriage_t *pCarriageInstance, arena_t *pArenaObj, buffer_t *pBufferObj, int inputArg)
{
//	ft_printf("Writing Operation\n");
// 	if (inputArg == CW_REG_CODE)
// 		ft_printf("Registr\n");
// 	else if (inputArg == CW_DIR_CODE)
// 		ft_printf("Direction\n");
// 	else if (inputArg == CW_IND_CODE)
// 		ft_printf("Indirection\n");
	char test = '1';
	//while (test != 'e')
	//	scanf("%c", &test);
	if (inputArg == CW_REG_CODE)
	{
		if (pArenaObj->pField[pCarriageInstance->currentLocation] > 0 && pArenaObj->pField[pCarriageInstance->currentLocation] < 17)
			pCarriageInstance->currentRegister = pArenaObj->pField[pCarriageInstance->currentLocation] - 1;
		else if ((pCarriageInstance->errorOcurred = CW_TRUE))
			return ;
//		ft_printf("Choosen reg: %d\n", pCarriageInstance->currentRegister);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
			pCarriageInstance->pRegisters[i + (pCarriageInstance->currentRegister * CW_REG_SIZE)] = pBufferObj->pData[i];
//		ft_printf("Next data was writen:\n");
// 		for (int i = 0; i < CW_REG_SIZE; ++i)
// 			ft_printf("%08b ", pBufferObj->pData[i]);
//		ft_printf("\n");
		pCarriageInstance->cwMoveTo(pCarriageInstance, CW_REG_CODE_SIZE);
	}
	else if (inputArg == CW_DIR_CODE)
	{
		// ft_printf("Next data was writen\n");
		// ft_printf("DirSize: %d\n", 4 - pCarriageInstance->pCurrentCommand->dirSize);
		for (int i = 4 - pCarriageInstance->pCurrentCommand->dirSize; i < CW_REG_SIZE; ++i)
		{
			pArenaObj->pField[pCarriageInstance->currentLocation] = pBufferObj->pData[i];
			// ft_printf("%08b ", pBufferObj->pData[i]);
			pCarriageInstance->cwMoveTo(pCarriageInstance, 1);
		}
	}
	else if (inputArg == CW_IND_CODE)
	{
		ft_memset(pArenaObj->paBufferSet[CW_SYSTEM_BUF]->pData, 0, CW_REG_SIZE);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i)
		{
			pArenaObj->paBufferSet[CW_SYSTEM_BUF]->pData[i] = pArenaObj->pField[pCarriageInstance->currentLocation];
			pCarriageInstance->cwMoveTo(pCarriageInstance, 1);
		}
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pArenaObj->paBufferSet[CW_SYSTEM_BUF], CW_SHORT);
		if (pCarriageInstance->pCurrentCommand->id != CW_LLD)
			pArenaObj->paBufferSet[CW_SYSTEM_BUF]->sTypes.shortValue %= IDX_MOD;
		// ft_printf("Ind readed: %d\n", pArenaObj->paBufferSet[CW_SYSTEM_BUF]->sTypes.shortValue);
		pCarriageInstance->cwSavePos(pCarriageInstance, CW_ADDIT_SAVE);
		pCarriageInstance->cwMoveTo					(pCarriageInstance, pArenaObj->paBufferSet[CW_SYSTEM_BUF]->sTypes.shortValue - pCarriageInstance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
		{
			pArenaObj->pField[pCarriageInstance->currentLocation] = pBufferObj->pData[i];
			pCarriageInstance->cwMoveTo(pCarriageInstance, 1);
		}
		// ft_printf("Next data was writen:\n");
		// for (int i = pCarriageInstance->currentLocation - 1; i > pCarriageInstance->currentLocation - 5; --i)
		// 	ft_printf("%08b ", pArenaObj->pField[i]);
		// ft_printf("\n");
		pCarriageInstance->cwCarriageReturn(pCarriageInstance, CW_ADDIT_SAVE);
	}
}

static void	cwReadOperation(carriage_t *pCarriageInstance, arena_t *pArenaObj, buffer_t *pBufferObj, int inputArg)
{
	// ft_printf("Reading operation\n");
	// if (inputArg == CW_REG_CODE)
	// 	ft_printf("Registr\n");
	// else if (inputArg == CW_DIR_CODE)
	// 	ft_printf("Direction\n");
	// else if (inputArg == CW_IND_CODE)
		// ft_printf("Indirection\n");
	char test = '1';
//	while (test != 'e')
//		scanf("%c", &test);
	if (inputArg == CW_REG_CODE)
	{
		if (pArenaObj->pField[pCarriageInstance->currentLocation] > 0 && pArenaObj->pField[pCarriageInstance->currentLocation] < 17)
			pCarriageInstance->currentRegister = pArenaObj->pField[pCarriageInstance->currentLocation] - 1;
		else if ((pCarriageInstance->errorOcurred = CW_TRUE))
			return ;
		// ft_printf("Choosen reg: %d\n", pCarriageInstance->currentRegister);
		// ft_memset(pBufferObj->pData, 0, CW_REG_SIZE);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
			pBufferObj->pData[i] = pCarriageInstance->pRegisters[i + (pCarriageInstance->currentRegister * CW_REG_SIZE)];
		// ft_printf("Next data was reading:\n");
		// for (int i = 0; i < CW_REG_SIZE; ++i)
		// 	ft_printf("%08b ", pBufferObj->pData[i]);
		// ft_printf("\n");
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pBufferObj, CW_INT);
		pCarriageInstance->cwMoveTo					(pCarriageInstance, CW_REG_CODE_SIZE);
	}
	else if (inputArg == CW_DIR_CODE)
	{
		ft_memset(pBufferObj->pData, 0, CW_REG_SIZE);
		// ft_printf("Next Data was readed\n");
		// ft_printf("DirSize: %d\n", 4 - pCarriageInstance->pCurrentCommand->dirSize);
		for (int i = 4 - pCarriageInstance->pCurrentCommand->dirSize; i < CW_REG_SIZE; ++i)
		{
			pBufferObj->pData[i] = pArenaObj->pField[pCarriageInstance->currentLocation];
			pCarriageInstance->cwMoveTo(pCarriageInstance, 1);
		}
		// for (int i = 4 - pCarriageInstance->pCurrentCommand->dirSize; i < CW_REG_SIZE; ++i)
		// 	ft_printf("%08b ", pBufferObj->pData[i]);
		// ft_printf("\n");
		pCarriageInstance->cwConversionBytesToValue(pCarriageInstance, pBufferObj, 4 - pCarriageInstance->pCurrentCommand->dirSize);
	}
	else if (inputArg == CW_IND_CODE)
	{
		ft_memset(pArenaObj->paBufferSet[CW_SYSTEM_BUF]->pData, 0, CW_REG_SIZE);
		ft_memset(pBufferObj->pData, 0, CW_REG_SIZE);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i)
		{
			pArenaObj->paBufferSet[CW_SYSTEM_BUF]->pData[i] = pArenaObj->pField[pCarriageInstance->currentLocation];
			pCarriageInstance->cwMoveTo(pCarriageInstance, 1);
		}
		pCarriageInstance->cwConversionBytesToValue	(pCarriageInstance, pArenaObj->paBufferSet[CW_SYSTEM_BUF], CW_SHORT);
		if (pCarriageInstance->pCurrentCommand->id != CW_LLD)
			pArenaObj->paBufferSet[CW_SYSTEM_BUF]->sTypes.shortValue %= IDX_MOD;
		// ft_printf("Ind readed: %d\n", pArenaObj->paBufferSet[CW_SYSTEM_BUF]->sTypes.shortValue);
		pCarriageInstance->cwSavePos(pCarriageInstance, CW_ADDIT_SAVE);
		pCarriageInstance->cwMoveTo					(pCarriageInstance, pArenaObj->paBufferSet[CW_SYSTEM_BUF]->sTypes.shortValue - pCarriageInstance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
		{
			pBufferObj->pData[i] = pArenaObj->pField[pCarriageInstance->currentLocation];
			pCarriageInstance->cwMoveTo(pCarriageInstance, 1);
		}
		// ft_printf("Next data was readed:\n");
		// for (int i = pCarriageInstance->currentLocation - 1; i > pCarriageInstance->currentLocation - 5; --i)
		// 	ft_printf("%08b ", pArenaObj->pField[i]);
		// ft_printf("\n");
		pCarriageInstance->cwCarriageReturn(pCarriageInstance, CW_ADDIT_SAVE);
	}
}

static void	cwParseTypes(carriage_t *pCarriageInstance, arena_t *pArenaObj)
{
	unsigned char	target;
	int				iter;
	char test = '1';

	iter = -1;
//	while (test != 'e')
//		scanf("%c", &test);
	// ft_printf("Parsing bytes...\n");
	// ft_printf("%032b\n", pCarriageInstance->pCurrentCommand->args);
	// ft_printf("%08b\n", pArenaObj->pField[pCarriageInstance->currentLocation]);
	// ft_printf("First arg: ------\n");
	target = pArenaObj->pField[pCarriageInstance->currentLocation];
	// ft_printf("%d\n", pCarriageInstance->currentLocation);
	if (pCarriageInstance->pCurrentCommand->typeByte)
	{
		if ((pCarriageInstance->pCurrentCommand->args >> 24) & 0xff)
		{
			// ft_printf("%032b\n", pCarriageInstance->pCurrentCommand->args >> 24);
			// ft_printf("%08b\n", (pArenaObj->pField[pCarriageInstance->currentLocation] >> 6) & 0x03);
			while (++iter < 3)
			{
				// ft_printf("%032b\n", pCarriageInstance->pCurrentCommand->args >> (26 + (iter * 2)));
				if (((pArenaObj->pField[pCarriageInstance->currentLocation] >> 6) & 0x03) & (pCarriageInstance->pCurrentCommand->args >> (26 + (iter * 2))))
					break;
			}
		}
		if (iter == 3 && (pCarriageInstance->errorOcurred = CW_TRUE))
			return ;
		// ft_printf("Second arg: ---------\n");
		iter = -1;
		if ((pCarriageInstance->pCurrentCommand->args >> 16) & 0xff)
		{
			// ft_printf("%032b\n", pCarriageInstance->pCurrentCommand->args >> 16);
			// ft_printf("%08b\n", (target >> 4) & 0x03);
			while (++iter < 3)
			{
				// ft_printf("%032b\n", pCarriageInstance->pCurrentCommand->args >> (18 + (iter * 2)));
				if (((pArenaObj->pField[pCarriageInstance->currentLocation] >> 4) & 0x03) & ((pCarriageInstance->pCurrentCommand->args >> (18 + (iter * 2))) & 0xff))
					break;
			}
		}
		if (iter == 3 && (pCarriageInstance->errorOcurred = CW_TRUE))
			return ;
		iter = -1;
		// ft_printf("Third arg: ---------\n");
		if ((pCarriageInstance->pCurrentCommand->args >> 8) & 0xff)
		{
			// ft_printf("%032b\n", pCarriageInstance->pCurrentCommand->args >> 8);
			// ft_printf("%08b\n", (target >> 2) & 0x03);
			while (++iter < 3)
			{
				// ft_printf("%032b\n", pCarriageInstance->pCurrentCommand->args >> (10 + (iter * 2)));
				if (((pArenaObj->pField[pCarriageInstance->currentLocation] >> 2) & 0x03) & (pCarriageInstance->pCurrentCommand->args >> (10 + (iter * 2))))
					break;
			}
		}
	}
	// ft_printf("Done...\n");
	if (iter == 3 && (pCarriageInstance->errorOcurred = CW_TRUE))
		return ;
	if (pCarriageInstance->pCurrentCommand->typeByte)
	{
		pCarriageInstance->firstArg		= (pArenaObj->pField[pCarriageInstance->currentLocation] & 0xc0) >> 6;
		pCarriageInstance->secondArg	= (pArenaObj->pField[pCarriageInstance->currentLocation] & 0x30) >> 4;
		pCarriageInstance->thirdArg		= (pArenaObj->pField[pCarriageInstance->currentLocation] & 0x0c) >> 2;
	}
	else
	{
		pCarriageInstance->firstArg		= CW_DIR_CODE;
		pCarriageInstance->secondArg	= CW_FALSE;
		pCarriageInstance->thirdArg		= CW_FALSE;
	}
	pCarriageInstance->cwMoveTo(pCarriageInstance, pCarriageInstance->pCurrentCommand->typeByte);
}

static void cwCarriageReturn(carriage_t *pCarriageInstance, int whereExactly)
{
	if (whereExactly == CW_MAIN_SAVE)
	{
		pCarriageInstance->currentLocation	= pCarriageInstance->savePoint;
		pCarriageInstance->odometer			= 0;
	}
	else if (whereExactly == CW_ADDIT_SAVE)
	{
		pCarriageInstance->currentLocation	= pCarriageInstance->additSavePoint;
		pCarriageInstance->odometer			= pCarriageInstance->additOdometer;
	}
}

static void	cwMoveTo(carriage_t *pCarraigeInstance, int distance)
{
	char test = '1';

//	while (test != 'e')
//		scanf("%c", &test);
	test = '1';
	// ft_printf("Moving\n");
	// ft_printf("Distance: %d\n", distance);
	// ft_printf("Before: %d\n", pCarraigeInstance->currentLocation);
	pCarraigeInstance->currentLocation		= (pCarraigeInstance->currentLocation + distance) % MEM_SIZE;
	if (pCarraigeInstance->currentLocation < 0)
		pCarraigeInstance->currentLocation	= MEM_SIZE + pCarraigeInstance->currentLocation;
	pCarraigeInstance->odometer += (distance % MEM_SIZE);
	// ft_printf("After: %d\n", pCarraigeInstance->currentLocation);
}

static void	cwSavePos(carriage_t *pCarriageInstance, int whichExactly)
{
	if (whichExactly == CW_MAIN_SAVE)
		pCarriageInstance->savePoint = pCarriageInstance->currentLocation;
	else if (whichExactly == CW_ADDIT_SAVE)
	{
		pCarriageInstance->additSavePoint	= pCarriageInstance->currentLocation;
		pCarriageInstance->additOdometer	= pCarriageInstance->odometer;
	}
}

static void	cwReduceWaitingTime(carriage_t *pCarraigeInstance)
{
	pCarraigeInstance->waitingTime -= 1;
	if (pCarraigeInstance->waitingTime < 0)
		cwErrorCatcher(CW_NOT_ALLOCATED, "Error in time reduce\n");
}

static void	cwExecCommand(carriage_t *pCarriageInstance, corewar_t *pGameInstance)
{
	pCarriageInstance->pCurrentCommand->cwCallback(pGameInstance);
	if (pCarriageInstance->errorOcurred == CW_TRUE)
		pCarriageInstance->cwReturnProtocolActivate(pCarriageInstance, pGameInstance->pArenaObj);
	pCarriageInstance->pCurrentCommand = NULL;
}

static void	cwSetCommandTime(carriage_t *pCarriageInstance, arena_t *pArenaInstance)
{
	int		errorCount;
	char test = '1';

	errorCount = 0;
	// ft_printf("Setting command\n");
	//while (test != 'e')
//		scanf("%c", &test);
	test = '1';
	while (pArenaInstance->pField[pCarriageInstance->currentLocation] < 1 || pArenaInstance->pField[pCarriageInstance->currentLocation] > 16)
	{
		if (++errorCount > MEM_SIZE)
			cwErrorCatcher(CW_NOT_ALLOCATED, "Error occured while trying to set command\n");
		pCarriageInstance->cwMoveTo(pCarriageInstance, 1);
	}
	pCarriageInstance->errorOcurred = CW_FALSE;
	pArenaInstance->test = &pCarriageInstance->currentLocation;
	pCarriageInstance->pCurrentCommand	= pCarriageInstance->ppCommandContainer[pArenaInstance->pField[pCarriageInstance->currentLocation]];
	pCarriageInstance->waitingTime		= pCarriageInstance->pCurrentCommand->waitingTime;
	pCarriageInstance->odometer			= 0;
	// ft_printf("Location: %d\n", pCarriageInstance->currentLocation);
	// ft_printf("Command: %d\n", pCarriageInstance->pCurrentCommand->id);
	pCarriageInstance->cwMoveTo	(pCarriageInstance, CW_NAME_PASS);
	pCarriageInstance->cwSavePos(pCarriageInstance, CW_MAIN_SAVE);
}

static void	cwSetOwner(carriage_t *pCarriageInstance, player_t *pPlayerList, int playerAmount)
{
	int		iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (iter < playerAmount)
	{
		if (pPlayerList->id == -pCarriageInstance->id)
			pCarriageInstance->pOwnerCarriage = pPlayerList;
		pPlayerList = pPlayerList->pNext;
		++iter;
	}
}

static void	cwReturnProtocolActivate(carriage_t *pCarriageInstance, arena_t *pArenaObj)
{
	int		lengthOfBrokenCode;
	int		iter;

	// ft_printf("Attention! Return Protocol Activate!\n");
	char test = '1';
	//while (test != 'a')
	//	scanf("%c", &test);
	lengthOfBrokenCode	= 0;
	iter				= 0;
	pCarriageInstance->cwCarriageReturn(pCarriageInstance, CW_MAIN_SAVE);
	if (pCarriageInstance->pCurrentCommand->typeByte)
	{
		pCarriageInstance->cwMoveTo(pCarriageInstance, 1);
		while (iter < 3)
		{
			if (((pArenaObj->pField[pCarriageInstance->currentLocation] << (iter * 2) & 0xc0) >> 6) == CW_REG_CODE)
				lengthOfBrokenCode += CW_REG_CODE;
			else if (((pArenaObj->pField[pCarriageInstance->currentLocation] << (iter * 2) & 0xc0) >> 6) == CW_DIR_CODE)
				lengthOfBrokenCode += CW_DIR_CODE;
			else if (((pArenaObj->pField[pCarriageInstance->currentLocation] << (iter * 2) & 0xc0) >> 6) == CW_IND_CODE)
				lengthOfBrokenCode += CW_IND_CODE;
			++iter;
		}
		pCarriageInstance->cwMoveTo(pCarriageInstance, lengthOfBrokenCode + 1);
	}
	else
		pCarriageInstance->cwMoveTo(pCarriageInstance, pCarriageInstance->pCurrentCommand->dirSize + 1);
}

/*
** Low level function for initialization object;
**--------------------------------------------------------------------------------------
*/

static void	cwConstructor(carriage_t **ppCarriageInstance)
{
	if (!((*ppCarriageInstance)->pRegisters = (unsigned char *)malloc(sizeof(unsigned char) * CW_REG_NUMBER * CW_REG_SIZE)))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	ft_memset((*ppCarriageInstance)->pRegisters, 0, CW_REG_NUMBER * CW_REG_SIZE);
	(*ppCarriageInstance)->id				= 0;
	(*ppCarriageInstance)->carry			= CW_FALSE;
	(*ppCarriageInstance)->waitingTime		= 0;
	(*ppCarriageInstance)->lastSpeakCycle	= 0;
	(*ppCarriageInstance)->additSavePoint	= 0;
	(*ppCarriageInstance)->currentLocation 	= 0;
	(*ppCarriageInstance)->firstArg			= 0;
	(*ppCarriageInstance)->secondArg		= 0;
	(*ppCarriageInstance)->thirdArg			= 0;
	(*ppCarriageInstance)->odometer			= 0;
	(*ppCarriageInstance)->additOdometer	= 0;
	(*ppCarriageInstance)->pCurrentCommand	= NULL;
	(*ppCarriageInstance)->pOwnerCarriage	= NULL;
	(*ppCarriageInstance)->pNext			= NULL;
	(*ppCarriageInstance)->pPrev			= NULL;
}

static void	cwDestructor(carriage_t **ppCarriageInstance)
{
	free((*ppCarriageInstance)->pRegisters);
	free((*ppCarriageInstance));
	*ppCarriageInstance = NULL;
}

extern void	cw_create_instance_carriage(carriage_t **ppCarriageObj)
{
	if (!(*ppCarriageObj = (carriage_t *)malloc(sizeof(carriage_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_CARRIAGE);
	(*ppCarriageObj)->cwConstructor				= cwConstructor;
	(*ppCarriageObj)->cwDestructor				= cwDestructor;
	(*ppCarriageObj)->cwConversionValueToBytes	= cwConversionValueToBytes;
	(*ppCarriageObj)->cwConversionBytesToValue	= cwConversionBytesToValue;
	(*ppCarriageObj)->cwReadOperation			= cwReadOperation;
	(*ppCarriageObj)->cwWriteOperation			= cwWriteOperation;
	(*ppCarriageObj)->cwParseTypes				= cwParseTypes;
	(*ppCarriageObj)->cwCheckCarry				= cwCheckCarry;
	(*ppCarriageObj)->cwSavePos					= cwSavePos;
	(*ppCarriageObj)->cwMoveTo					= cwMoveTo;
	(*ppCarriageObj)->cwExecCommand				= cwExecCommand;
	(*ppCarriageObj)->cwSetCommandTime			= cwSetCommandTime;
	(*ppCarriageObj)->cwReduceTime				= cwReduceWaitingTime;
	(*ppCarriageObj)->cwWriteOwnerIdToReg		= cwWriteOwnerIdToReg;
	(*ppCarriageObj)->cwCarriageReturn			= cwCarriageReturn;
	(*ppCarriageObj)->cwReturnProtocolActivate	= cwReturnProtocolActivate;
	(*ppCarriageObj)->cwSetOwner				= cwSetOwner;
	(*ppCarriageObj)->cwCopyReg					= cwCopyReg;
	(*ppCarriageObj)->cwConstructor				(ppCarriageObj);
}

/*
**--------------------------------------------------------------------------------------
*/