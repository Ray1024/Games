/**********************************************************************
@file		SceneStart.h
@brief		”Œœ∑≤Àµ•≥°æ∞
@author		Jianlei Guo
@date		2016-9-22
***********************************************************************/

#ifndef __SCENESTART_H__
#define __SCENESTART_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneStart : public Layer
{
public:
    static Scene* scene();

    bool init();

    CREATE_FUNC(SceneStart);

	void CallMenu(Node* sender);
};

#endif // !__SCENESTART_H__

