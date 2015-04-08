#include "module.h"

Module::~Module()
{
}

Board & Module::oGetBoard() const
{
	return const_cast<Board&>(moBoard);
}

Module::MODULE_TYPE Module::eGetType() const
{
	return meType;
}

bool Module::bIsGame() const
{
	return (meType == Module::MT_GAME);
}