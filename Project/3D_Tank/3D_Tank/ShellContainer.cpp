#include "ShellContainer.h"
#include "Shell.h"

ShellContainer* ShellContainer::sInstance = NULL;

ShellContainer * ShellContainer::sGetInstance()
{
	if (sInstance == NULL)
		sInstance = new ShellContainer();
	return sInstance;
}

void ShellContainer::onInit()
{
	if (sInstance == NULL)
		sInstance = new ShellContainer();
}

void ShellContainer::destroy()
{
	delete sInstance;
	sInstance = NULL;
}

ShellContainer::ShellContainer()
{
}

ShellContainer::~ShellContainer()
{
}

std::vector<Shell*> ShellContainer::getOnTriggerShells()
{
	return onTriggerShells;
}

std::vector<Shell*> ShellContainer::getUnTriggerShells()
{
	return unTriggerShells;
}
