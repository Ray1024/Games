#include "AIPlayer.h"  

AIPlayer::AIPlayer(SceneGame* _gameScene){  
		this->gameScene = _gameScene;  
}  

AIPlayer::~AIPlayer(){}  

//enum TYPE { JIANG, SHI, XIANG, JU, MA, PAO, BING }; �������ӵķ�ֵ��Ӧ  
int AIPlayer::stone_scores[7] = { 1500, 10, 10, 100, 50, 50, 20 };  

int AIPlayer::getScores()
{  
	int black_score = 0;  
	int red_score = 0;  
	for (int i = 0; i < 32; i++)
	{  
		Stone* stone = gameScene->_s[i];  
		if (!stone->getDead())
		{  
			if (stone->getRed())
			{  
				red_score += stone_scores[stone->getType()];  
			}  
			else
			{  
				black_score += stone_scores[stone->getType()];  
			}  
		}  
	}  
	return black_score - red_score;  
}  

Array* AIPlayer::getAllPosibleStep()
{  
	Array* stepsArray = Array::create();  
	if (gameScene->_redSide)
	{
		for (int i = 16; i < 32; i++)
		{  
			getAllPosibleStep(i, stepsArray);  
		}
	}
	else
	{
		for (int i = 0; i < 16; i++)
		{  
			getAllPosibleStep(i, stepsArray);  
		}
	}
	return stepsArray;  
}  

void AIPlayer::getAllPosibleStep(int i, Array* stepArray)
{  
	Stone* stone = gameScene->_s[i];  
	if (stone->getDead()) return;  

	for (int x = 0; x < 9; x++)
	{  
		for (int y = 0; y < 10; y++)
		{  
			// �������λ�����ѷ�������
			int killID = gameScene->getStone(x, y);
			if (killID != -1 && gameScene->_s[killID]->getRed() == stone->getRed())
			{  
				continue;  
			}  
			// �������λ���ǵ�ǰλ��
			if (stone->getX() == x && stone->getY() == y)
			{  
				continue;  
			}  
			// �������λ��û���ѷ������ӣ��Ҳ��ǵ�ǰλ�ã�����������������ӵ�������λ��������
			if (gameScene->canMove(stone->getID(), killID, x, y))
			{  
				Step* step = Step::create(stone->getID(), killID, stone->getX(), stone->getY(),x, y);  
				stepArray->addObject(step);  
			}  
		}  
	}  
} 

Step* AIPlayer::getOneMoveAction(int level)
{  
	int maxScore = -100000;  
	Step* reStep;  
	Array* possibleMove = getAllPosibleStep();  
	Ref* obj;  
	CCARRAY_FOREACH(possibleMove, obj)
	{  
		Step* step = (Step*)obj;  
		gameScene->fakeMove(step);  
		int score = getMinScore(level - 1, maxScore);  
		gameScene->unfakeMove(step);  
		if (score > maxScore) 
		{  
			maxScore = score;
			reStep = step;  
		}  
	}  
	return reStep;  
}  

int AIPlayer::getMinScore(int level, int max)
{  
	if (level <= 0)
	{  
		return getScores();  
	}  
	int minScore = 100000;  
	Step* reStep;  
	Array* possibleMove = getAllPosibleStep();  
	Object* obj;  
	CCARRAY_FOREACH(possibleMove, obj){  
		Step* step = (Step*)obj;  
		gameScene->fakeMove(step);  
		int score = getMaxScore(level - 1, minScore);  
		gameScene->unfakeMove(step);  
		if (score >= max) {  
			return score;  
		}  
		if (score < minScore){  
			minScore = score;  
		}  
	}  
	return minScore;  
}  

int AIPlayer::getMaxScore(int level, int min)
{  
	if (level <= 0)
	{  
		return getScores();  
	}  
	int maxScore = -100000;  
	Step* reStep;  
	Array* possibleMove = getAllPosibleStep();  
	Object* obj;  
	CCARRAY_FOREACH(possibleMove, obj)
	{  
		Step* step = (Step*)obj;  
		gameScene->fakeMove(step);  
		int score = getMinScore(level - 1, maxScore);  
		gameScene->unfakeMove(step);  
		if (score <= min) 
		{  
			return score;  
		}  
		if (score > maxScore)
		{  
			maxScore = score;  
		}  
	}  
	return maxScore;  
}  