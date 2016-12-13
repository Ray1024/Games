/**********************************************************************
@file		SceneMenu.h
@brief		”Œœ∑≤Àµ•≥°æ∞
@author		Jianlei Guo
@date		2016-9-22
***********************************************************************/

#ifndef __SCENEMENU_H__
#define __SCENEMENU_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneMenu : public Layer
{
public:
    static Scene* scene();

    bool init();

    CREATE_FUNC(SceneMenu);

	void menuBeginGame(Ref*);
	void menuExit(Ref*);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif // !__SCENEMENU_H__

