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

void ShellContainer::applyShell(const Vector3 & position, const Vector3 & direction, const int & shelType)
{
	if (unTriggerShells.size() == 0) {
		Shell* shell = new Shell(position, direction, shelType);
	}
	else {
		(*unTriggerShells.begin())->resetPosAndDir(position, direction, shelType);
	}
}
