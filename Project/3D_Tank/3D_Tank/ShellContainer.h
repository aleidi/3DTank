#pragma once
#include <vector>
#include "Vector3.h"

class Shell;

class ShellContainer {
public:
	static ShellContainer* sGetInstance();
	static void onInit();
	static void destroy();

	std::vector<Shell*> getOnTriggerShells();
	std::vector<Shell*> getUnTriggerShells();

	void applyShell(const Vector3& position, const Vector3& direction, const int& shelType);

private:
	static ShellContainer* sInstance;
	ShellContainer();
	~ShellContainer();
	ShellContainer(const ShellContainer&) = delete;
	ShellContainer & operator=(const ShellContainer&) = delete;

private:
	friend class Shell;

	std::vector<Shell*>onTriggerShells;
	std::vector<Shell*>unTriggerShells;
};