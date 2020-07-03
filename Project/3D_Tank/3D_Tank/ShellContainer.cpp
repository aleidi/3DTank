#include "ShellContainer.h"
#include "Shell.h"
#include "GameObject.h"
#include "ShellFlyComponent.h"

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
	if (unTriggerShells.size() > 5) {
		for (std::vector<Shell*>::iterator it = unTriggerShells.begin() + 5; it != unTriggerShells.end();) {
			(*it)->shell->destroy();
			(*it)->destroy();
			it = unTriggerShells.erase(it);
		}
	}
}

void ShellContainer::applyShell(const Vector3 & position, const Vector3 & direction, const int & shelType, GameObject * target)
{
	if (unTriggerShells.size() == 0) {
		Shell* shell = new Shell(position, direction, shelType);
		shell->getShellComponent()->setTarget(target);
	}
	else {
		(*unTriggerShells.begin())->resetPosAndDir(position, direction, shelType);
		(*unTriggerShells.begin())->getShellComponent()->setTarget(target);
	}
	if (unTriggerShells.size() > 5) {
		for (std::vector<Shell*>::iterator it = unTriggerShells.begin() + 5; it != unTriggerShells.end();) {
			(*it)->shell->destroy();
			(*it)->destroy();
			it = unTriggerShells.erase(it);
		}
	}
}
