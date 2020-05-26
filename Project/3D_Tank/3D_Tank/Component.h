#include"Object.h"

class Component
{
protected:
	Object* object;

public:
	bool setObject(Object obj);
	Object getObject();
};