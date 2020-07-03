#pragma once
#include <vector>

class Shell;

class ShellContainer {
public:
	static ShellContainer* sGetInstance();
	static void onInit();
	static void destroy();

	std::vector<Shell*> getOnTriggerShells();
	std::vector<Shell*> getUnTriggerShells();

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