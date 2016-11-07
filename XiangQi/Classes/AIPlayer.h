/**********************************************************************
@file		AIPlayer.h
@brief		µçÄÔAI
@author		Jianlei Guo
@date		2016-9-22
***********************************************************************/

#ifndef __AIPLAYER_H__
#define __AIPLAYER_H__

#include "cocos2d.h"
#include "AppMacros.h"
#include "SceneGame.h"  
USING_NS_CC;

//Æå×ÓÀà
class AIPlayer  
{  
public:  
	AIPlayer(SceneGame* _gameScene);  
	~AIPlayer();  
	Step* getOneMoveAction(int level);  
	int getScores();  
	Array* getAllPosibleStep();  
	void getAllPosibleStep(int i, Array* stepArray);  
	int getMinScore(int level, int max);  
	int getMaxScore(int level, int min);  
public:  
	SceneGame* gameScene;  
	static int stone_scores[7];  
};  

#endif	// !__AIPLAYER_H__
