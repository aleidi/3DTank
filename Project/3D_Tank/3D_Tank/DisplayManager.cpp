#include <assert.h>

#include "DisplayManager.h"
#include "DamageDisplay.h"

DisplayManager* DisplayManager::sInstance = nullptr;

DisplayManager * DisplayManager::sGetInstance()
{
	return sInstance;
}

void DisplayManager::createSingleton()
{
	assert(!sInstance);
	sInstance = new DisplayManager();
}

DisplayManager::DisplayManager()
	:mTexts(),mMaxTexts(30)
{
	createText();
}

DisplayManager::~DisplayManager()
{
}

void DisplayManager::displayText(const std::wstring & text, float sizeX, float sizeY, const Vector3 & start, float transition, float aliveTime, float upValue, float speed)
{
	int count{ 0 };
	for (std::vector<DamageDisplay*>::iterator it = mTexts.begin(); it != mTexts.end(); ++it)
	{
		++count;
		if (!(*it)->isEnable())
		{
			(*it)->setText(text);
			(*it)->setStartPosition(start);
			(*it)->setTransition(transition);
			(*it)->setAliveTime(aliveTime);
			(*it)->setUpValue(upValue);
			(*it)->setSpeed(speed);
			(*it)->setSizeScale(sizeX, sizeY);
			(*it)->setEnable(true);
			std::swap(mTexts[count-1],mTexts[mTexts.size()-1]);
			return;
		}
	}

	if (count < mMaxTexts)
	{
		createText();
		count = mTexts.size() - 1;	
		mTexts[count]->setText(text);
		mTexts[count]->setStartPosition(start);
		mTexts[count]->setTransition(transition);
		mTexts[count]->setAliveTime(aliveTime);
		mTexts[count]->setUpValue(upValue);
		mTexts[count]->setSpeed(speed);
		mTexts[count]->setSizeScale(sizeX, sizeY);
		mTexts[count]->setEnable(true);
		return;
	}

	mTexts[0]->setText(text);
	mTexts[0]->setStartPosition(start);
	mTexts[0]->setTransition(transition);
	mTexts[0]->setAliveTime(aliveTime);
	mTexts[0]->setUpValue(upValue);
	mTexts[0]->setSpeed(speed);
	mTexts[0]->setSizeScale(sizeX, sizeY);
	mTexts[0]->setEnable(true);
}

void DisplayManager::setTextAmount(int value)
{
	mMaxTexts = value;
}

int DisplayManager::getMaxText()
{
	return mTexts.size();
}

void DisplayManager::createText()
{
	mTexts.push_back(new DamageDisplay());
}
