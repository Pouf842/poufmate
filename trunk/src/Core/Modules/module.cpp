#include "module.h"

Module::~Module()
{
}

void Module::SetInterface(Interface * poInterface)
{
	mpoInterface = poInterface;
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

Piece::PIECE_TYPE Module::eGetSelectedPieceType() const
{
	return meSelectedPieceType;
}

Piece::PIECE_COLOR Module::eGetSelectedPieceColor() const
{
	return meSelectedPieceColor;
}