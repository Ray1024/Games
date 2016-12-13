/**********************************************************************
@file		SceneGame.h
@brief		”Œœ∑≥°æ∞
@author		Jianlei Guo
@date		2016-12-13
***********************************************************************/

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneGame : public cocos2d::Layer
{
public:
    virtual bool init();  

    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuBackCallback(Ref* sender);
    
    CREATE_FUNC(SceneGame);
};

#endif // __GAME_SCENE_H__
