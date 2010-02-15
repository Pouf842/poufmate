#include "module.h"

Module::~Module()
{
}

void Module::SetInterface(Interface * poInterface)
{
	mpoInterface = poInterface;
}