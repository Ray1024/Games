#include "SceneGame.h"
#include "AppMacros.h"
#include "SceneMenu.h"
#include "AIPlayer.h"

SceneGame::SceneGame()
	: _select(NULL)
	, _result(NULL)
	, _ai(NULL)
	, _lose(NULL)
{
}

SceneGame::~SceneGame()
{
	CC_SAFE_RELEASE_NULL(_select);
	CC_SAFE_RELEASE_NULL(_result);
	CC_SAFE_RELEASE_NULL(_lose);
	CC_SAFE_DELETE(_ai);
}

Scene* SceneGame::scene(bool red)
{
    Scene* scene = Scene::create();

    SceneGame* layer = SceneGame::create(red);

    scene->addChild(layer);

    return scene;
}

SceneGame* SceneGame::create(bool red)
{
	SceneGame *ret = new SceneGame();
	if (ret && ret->init(red))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}
}

bool SceneGame::init(bool red)
{
    if(!Layer::init())   return false;

	Size winSize = Director::getInstance()->getWinSize();

	_ai = new AIPlayer(this);

	// 为变量赋值------------------------------------------------------------------
	// 设置棋盘的偏移值
	this->_plateOffset = Point(0/SCALE_FACTOR,200/SCALE_FACTOR);

	// 设置棋子的偏移值
	this->_stoneOffset = Point(45/SCALE_FACTOR, 220/SCALE_FACTOR);

	// 玩家是否为红方
	_redSide = red;

	// 初始化时，没有选中棋子
	_selectid = -1;

	// 走棋时，切换棋子的颜色
	_redTurn = true;

	// 创建游戏元素------------------------------------------------------------------
	// 创建桌子
	Sprite* desk = Sprite::create("bg_game.jpg");
	this->addChild(desk,-2);
	desk->setPosition(Point(winSize.width / 2, winSize.height / 2));
	desk->setScaleX(winSize.width / desk->getContentSize().width);
	desk->setScaleY(winSize.height / desk->getContentSize().height);
	
    // 创建棋盘
    Sprite* plate = Sprite::create("background.png");
    this->addChild(plate,-1);
    plate->setAnchorPoint(Point(0,0));
    plate->setPosition(_plateOffset);
    // 让棋盘和屏幕宽度一致
    plate->setScale((winSize.width -_plateOffset.x *2)/ plate->getContentSize().width);

    //摆棋子
    for(int i=0; i<32; i++)
    {
		//创建棋子
		_s[i] = Stone::create(i, red);
		addChild(_s[i],1);

		//隐藏棋子
		_s[i]->setVisible(false);
    }

    // 棋子的蓝色选择框
    _select = Sprite::create("selected.png");
	_select->retain();
    addChild(_select);
    _select->setVisible(false);
    _select->setLocalZOrder(1000);
    _select->setScale(0.991f);

	// 创建游戏结果显示
	_result = Sprite::create("win.png");
	_result->retain();
	addChild(_result);
	_result->setPosition(Point(winSize.width / 2, winSize.height / 2));
	_result->setVisible(false);

	_lose = Sprite::create("lose.png");
	_lose->retain();
	addChild(_lose);
	_lose->setPosition(Point(winSize.width / 2, winSize.height / 2));
	_lose->setVisible(false);

    // 创建Menu---------------------------------------------------------------------
	Menu* menu = Menu::create();
	this->addChild(menu);
	menu->setPosition(270/SCALE_FACTOR, 860/SCALE_FACTOR);
	
    MenuItem* itemStart = MenuItemImage::create("button_start.png", "button_start.png", CC_CALLBACK_1(SceneGame::Start,this));
    menu->addChild(itemStart);
    itemStart->setPosition(-160/SCALE_FACTOR,0/SCALE_FACTOR);

    MenuItem* item = MenuItemImage::create("button_regret.png", "button_regret.png",CC_CALLBACK_1(SceneGame::Back,this));
    menu->addChild(item);
    item->setPosition(0/SCALE_FACTOR,0/SCALE_FACTOR);

    MenuItem* itemVoice = MenuItemImage::create("button_openVolice.png","button_closeVolice.png",CC_CALLBACK_1(SceneGame::Voice,this));
    menu->addChild(itemVoice);
    itemVoice->setPosition(160/SCALE_FACTOR,0/SCALE_FACTOR);

	// 播放背景音乐------------------------------------------------------------------
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bg.mp3",true);

	// 注册事件触发------------------------------------------------------------------
    // 注册触摸事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SceneGame::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SceneGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 注册手机键盘的事件
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(SceneGame::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

    return true;
}

bool SceneGame::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

//通过点击选择棋子，走棋子
void SceneGame::onTouchEnded(Touch *touch, Event *unused_event)
{
    // 获取触摸点的窗口坐标
    Point pt = touch->getLocation();

	// 点击胜游戏结果
	if(_result->isVisible())  
	{  
		if (_result->getBoundingBox().containsPoint(pt))
		{
			// 隐藏游戏结果并开始新游戏
			_result->setVisible(false);
			_result->setScale(1.f);
			Start(NULL);
		}
		return;
	}

	// 点击负游戏结果
	if(_lose->isVisible())  
	{  
		if (_lose->getBoundingBox().containsPoint(pt))
		{
			// 隐藏游戏结果并开始新游戏
			_lose->setVisible(false);
			_lose->setScale(1.f);
			Start(NULL);
		}
		return;
	}

	int x, y;//保存触摸点的棋盘索引

	if(!getClickPos(pt, x, y))
	{
		return;
	}

	//通过触摸点在棋盘中的坐标获取选中的棋子的id
	int clickid = getStone(x, y);
	//当触摸点的位置上有棋子的时候,clickid为选中的棋子的id,表示玩家在选棋
	//当触摸点的位置上没有棋子的时候,clickid为-1,表示玩家在走棋

	//-1 == _selectid表示没有选中棋子
	if(-1 == _selectid)
	{
		setSelectId(clickid);
	}
	else
	{
		//移动棋子
		//参数1：移动的棋子的id
		//参数2：通过触摸点的位置判断触摸点上是否有棋子
		//参数3：触摸点的x坐标
		//参数4：触摸点的y坐标
		//moveStone执行了两个步骤选棋和走棋
		//选棋子：当_selectid == clickid时，表示选定了id为_selectid的棋子
		//走棋子：当selectid != clickid时， 表示将id为_selectid的棋子移动到(x,y)所在的位置上
		moveStone(_selectid, clickid, x, y);
	}
}

void SceneGame::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)  //返回开始菜单
	{
		auto transition=TransitionFade::create(1.0f,SceneMenu::scene());
		Director::getInstance()->replaceScene(transition);
		CocosDenshion::SimpleAudioEngine::getInstance()->end();// 结束音频
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_MENU)
	{
		// TODO: 设置菜单
	}
}

Point SceneGame::getStonePos(int x, int y)
{
	int xx = x * Stone::DIAMETER;
	int yy = y * Stone::DIAMETER;

	return Point(xx, yy) + _stoneOffset;
}

bool SceneGame::getClickPos(Point pt, int &x, int &y)
{
	for(x=0; x<=8; x++)
	{
		for(y=0; y<=9; y++)
		{
			// 计算棋盘上的格子在窗口上的位置
			Point ptInPlate = getStonePos(x, y);

			// 寻找与鼠标点击的位置距离小于棋子的半径的格子
			// 如果找到了,return true,否则返回 return false
			if(pt.getDistance(ptInPlate) < Stone::DIAMETER / 2)
			{
				return true;
			}
		}
	}

	return false;
}

//通过坐标的下标获取棋子的ID
//如果坐标上没有棋子,返回-1
int SceneGame::getStone(int x, int y)
{
	Stone* s;

	// 遍历32个棋子
	for(int i=0; i<32; i++)
	{
		s = _s[i];

		if(s->getX()==x && s->getY()==y && !s->getDead())
		{
			// 得到棋子的ID
			return s->getID();
		}
	}

	return -1;
}

//更换选择框
void SceneGame::setSelectId(int id)
{
	if(-1 == id)
	{
		return;
	}

	// 如果该红方走，黑方棋子跳过，反之则反
	if(_s[id]->getRed() != _redTurn)
	{
		return;
	}

	// _selectid为选中的棋子的id
	_selectid = id;

	// 显示选择框
	_select->setVisible(true);
	_select->setPosition(_s[_selectid]->getPosition());
}

void SceneGame::moveStone(int moveId, int killId, int x, int y)
{
	// 如果killId标识有棋子，而且棋子和已经选中的棋子颜色一样，切换选择，跳过以下操作
	if(killId != -1 && _s[moveId]->getRed() == _s[killId]->getRed())
	{
		// 更换选择框
		setSelectId(killId);
		return;
	}
	
	// 判断是否符合走棋规则
	if(!canMove(moveId, killId, x, y))
	{
		return;
	}

	// 记录走棋的信息
	Step* step = Step::create(moveId, killId, _s[moveId]->getX(), _s[moveId]->getY(), x, y);
	_steps.pushBack(step);

	// 设置棋子的索引坐标(移动棋子)
	_s[moveId]->setX(x);
	_s[moveId]->setY(y);

	// 设置移动棋子动作
	MoveTo* move = MoveTo::create(0.3f, getStonePos(x, y));
	
	// 动作回调
	CCCallFuncND* call = CCCallFuncND::create(this, callfuncND_selector(SceneGame::moveComplete),(void*)killId);

	// 设置动作的执行顺序(先移动棋子,后调用回调函数)
	Sequence* seq = Sequence::create(move, call, NULL);

	// 设置移动的棋子的优先级
	_s[moveId]->setLocalZOrder(_s[moveId]->getLocalZOrder() + 1);

	// 执行棋子移动的动作
	_s[moveId]->runAction(seq);
}

void SceneGame::moveComplete(Node* movestone, void* _killid)
{
	Size winSize = Director::getInstance()->getWinSize();

	// 设置优先级
	movestone->setLocalZOrder(movestone->getLocalZOrder() - 1);

	int killid =  (int)(intptr_t)_killid;

	// 如果触摸点上有棋子
	if(-1 != killid)
	{
		// 杀掉触摸点上的棋子
		_s[killid]->setDead(true);

		// 隐藏杀掉的棋子
		_s[killid]->setVisible(false);

		// 当杀掉将的时候,重新开始
		if(Stone::JIANG  == _s[killid]->getType())
		{
			if (_s[killid]->getRed()==_redSide)
			{
				// 显示游戏结果
				_lose->setVisible(true);
				_lose->runAction(ScaleBy::create(0.6f,6));

				// 设置优先级
				_lose->setLocalZOrder(1000);
			}
			else
			{
				// 显示游戏结果
				_result->setVisible(true);
				_result->runAction(ScaleBy::create(0.6f,6));

				// 设置优先级
				_result->setLocalZOrder(1000);
			}
		}
	}

	// 播放走子音效
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("go.wav");

	// 没有选中棋子
	_selectid = -1;

	// 隐藏选择框
	_select->setVisible(false);

	// 移动了一步棋后
	// 切换移动的棋子的颜色
	_redTurn = ! _redTurn;

	if (!_result->isVisible() && _redTurn == !_redSide)
	{  
		aiGostep();  
	}  
}

void SceneGame::Back(Ref*)
{
	// 当数组中的元素个数为0时，没走棋
	if(0 == _steps.size())
	{
		return;
	}

	// 获取上一次的走棋信息
	Step* step = _steps.back();

	// 恢复棋子的信息
	_s[step->_moveid]->setX(step->_xFrom);
	_s[step->_moveid]->setY(step->_yFrom);
	_s[step->_moveid]->setPosition(getStonePos(step->_xFrom, step->_yFrom));

	// 恢复吃掉的棋子
	if(step->_killid != -1)
	{
		//显示吃掉的棋子
		_s[step->_killid]->setVisible(true);
		//复活吃掉的棋子
		_s[step->_killid]->setDead(false);
	}

	//悔棋后，切换移动棋子的颜色
	_redTurn = ! _redTurn;

	// 删除上一次的走棋信息
	_steps.popBack();
}

void SceneGame::Start(Ref*)
{
	scheduleOnce(schedule_selector(SceneGame::updateAutoGo), 1.0f); 
	// 将棋子恢复至起始
	for(int i = _steps.size(); i>0; i--)
	{
		Back(NULL);
	}

	// 摆棋子
	for(int i=0; i<32; i++)
	{
		_s[i]->setPosition(getStonePos(_s[i]->getX(), _s[i]->getY()));
		_s[i]->setVisible(true);
	}
}

void SceneGame::Voice(Ref* sender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	auto soundItem = (MenuItemImage*)sender;

    if(audio->isBackgroundMusicPlaying())
    {   // 暂停背景音乐
		audio->pauseBackgroundMusic();
		soundItem->selected();
    }
    else
    {   // 继续背景音乐
        audio->resumeBackgroundMusic();
		soundItem->unselected();
    }
}

// 走棋规则
bool SceneGame::canMove(int moveid, int killid, int x, int y)
{
    // 获得选中的棋子
    Stone* s = _s[moveid];

    // 棋子的类型
    switch(s->getType())
    {
        // 将的走棋规则
        case Stone::JIANG:
        {
            return canMoveJiang(moveid, killid, x, y);
        }
        break;

        // 士的走棋规则
        case Stone::SHI:
        {
            return canMoveShi(moveid, x, y);
        }
        break;

        // 相的走棋规则
        case Stone::XIANG:
        {
            return canMoveXiang(moveid, x, y);
        }
        break;
       
        // 车的走棋规则
        case Stone::CHE:
        {
            return canMoveChe(moveid, x, y);
        }
        break;
       
        // 马的走棋规则
        case Stone::MA:
        {
            return canMoveMa(moveid, x, y);
        }
        break;
    
        // 炮的走棋规则
        case Stone::PAO:
        {
            return canMovePao(moveid, killid, x, y);
        }
        break;
     
        // 兵的走棋规则
        case Stone::BING:
        {
            return canMoveBing(moveid, x, y);
        }
        break;

        default:
        {
            break;
        }
    }

    return false;
}


//将的走棋规则
bool SceneGame::canMoveJiang(int moveid, int killid, int x, int y)
{
	/* 将的走棋规则：
	1、一次走一格 
	2、不能出九宫格
	3、将可以对杀
	*/

	if (killid != -1)
	{
		Stone* skill = _s[killid];
	
		// 将的对杀
		if(skill->getType() == Stone::JIANG)
		{
			return canMoveChe(moveid, x, y);
		}
	}

    // 通过棋子的ID得到棋子
    Stone* s = _s[moveid];

    // 获得将当前的位置
    int xo = s->getX();
    int yo = s->getY();

    // 获得将走的格数
    // (x,y)表示将走到的位置
    int xoff = abs(xo - x);
    int yoff = abs(yo - y);
    
    int d = xoff*10 + yoff;

    // 走将的时候有两种情况
    //xoff=1, yoff=0：将向左或向右
    //xoff=0, yoff=1：将向前或向后
    if(d != 1 && d != 10)
    {
        return false;
    }

    //判断将是否出了九宫
    //红色的将和黑色的将的x坐标的范围都是3<=x<=5
    if(x<3 || x>5)
    {
        return false;
    }

    //如果玩家的棋子是红棋
    if(_redSide == s->getRed())
    {
        //判断将是否出了九宫
        if(y<0 || y>2)
        {
            return false;
        }
    }
    else//判断黑色的将的范围
    {
        //判断将是否出了九宫
        if(y>9 || y<7)
        {
            return false;
        }
    }

    return true;
}


//士的走棋规则
bool SceneGame::canMoveShi(int moveid, int x, int y)
{
    //士的走棋规则：
    //1、一次走一格
    //2、不能出九宫格
   //3、斜着走

     //通过棋子的ID得到棋子
    Stone* s = _s[moveid];

    //获得相走棋前的位置
    int xo = s->getX();
    int yo = s->getY();

    //获得相走的格数
    //(x,y)表示将走到的位置
    int xoff = abs(xo - x);
    int yoff = abs(yo - y);

    int d = xoff*10 + yoff;

    //士每走一步x方向走1格,y方向走1格
    //当走的格数大于1格时
    //返回false
    if(d != 11)
    {
        return false;
    }

     //判断士是否出了九宫
    //红色的士和黑色的士的x坐标的范围都是3<=x<=5
    if(x<3 || x>5)
    {
        return false;
    }

    //如果玩家的棋子是红棋
    if(_redSide == s->getRed())
    {
        //判断士是否出了九宫
        if(y<0 || y>2)
        {
            return false;
        }
    }
    else//判断黑色的士的范围
    {
        //判断士是否出了九宫
        if(y>9 || y<7)
        {
            return false;
        }
    }

    return true;
}


//相的走棋规则
bool SceneGame::canMoveXiang(int moveid, int x, int y)
{
     //相的走棋规则：
    //每走一次x移动2格,y移动2格
    //不能过河


    //通过棋子的ID得到棋子
    Stone* s = _s[moveid];

    //获得相走棋前的位置
    int xo = s->getX();
    int yo = s->getY();

    //获得相走的格数
    //(x,y)表示将走到的位置
    int xoff = abs(xo - x);
    int yoff = abs(yo - y);

    int d = xoff*10 + yoff;

    //相每一次x方向走2格子,y方向走2格
    //当走的格数大于2格时
    //返回false
    if(d != 22)
    {
        return false;
    }

    //计算两个坐标的中点坐标
    int xm = (xo + x) / 2;
    int ym = (yo + y) / 2;

    //得到(xm,ym)上的棋子
    int id = getStone(xm, ym);

    //当(xm,ym)上有棋子的时候
    if(id != -1)
    {
        //不能走相
        return false;
    }

	//限制相不能过河
	//如果玩家的棋子是红棋
    if(_redSide == s->getRed())
    {
        //判断相是否过了河
        if(y > 4)
        {
            return false;
        }
    }
    else//判断黑色的相的范围
    {
         //判断相是否过了河
        if(y < 5)
        {
            return false;
        }
    }

    return true;
}


//车的走棋规则
bool SceneGame::canMoveChe(int moveid, int x, int y)
{
    //通过棋子的ID得到棋子
    Stone* s = _s[moveid];

    //获得车走棋前的位置
    int xo = s->getX();
    int yo = s->getY();

    //当两点之间有棋子的时候车不能走
    if(getStoneCount(xo,yo,x,y) != 0)
    {
        return false;
    }

    return true;
}


//马的走棋规则
bool SceneGame::canMoveMa(int moveid, int x, int y)
{
    //通过棋子的ID得到棋子
    Stone* s = _s[moveid];

     //获得马走棋前的位置
    int xo = s->getX();
    int yo = s->getY();
    
     //获得马走的格数
    //(x,y)表示马走到的位置
    //马有两种情况：
    //第一种情况：马先向前或向后走1步，再向左或向右走2步
    //第二种情况：马先向左或向右走1不，再向前或向后走2步
    int xoff = abs(xo-x);
    int yoff = abs(yo-y);
    
    int d = xoff*10 + yoff;
    
    if(d != 12 && d != 21)     
    {
        return false;
    }

    int xm, ym;//记录绑脚点坐标
   
    if(d == 12)//当马走的是第一种情况
    {
        xm = xo;//绑脚点的x坐标为走棋前马的x坐标
        ym = (yo + y) / 2;//绑脚点的y坐标为走棋前马的y坐标和走棋后马的y坐标的中点坐标
    }
    else//当马走的是第二种情况
    {
        xm = (xo + x) / 2;//绑脚点的x坐标为走棋前马的x坐标和走棋后马的x坐标的中点坐标
        ym = yo;;//绑脚点的y坐标为走棋前马的y坐标
    }
    
    //当绑脚点有棋子时,不能走
    if(getStone(xm, ym) != -1) 
    {
        return false;
    }

    return true;
}


//炮的走棋规则
bool SceneGame::canMovePao(int moveid, int killid, int x, int y)
{
    //通过棋子的ID得到棋子
    Stone* s = _s[moveid];

    //获得炮走棋前的位置
    int xo = s->getX();
    int yo = s->getY();

    //当触摸点上有一个棋子
    //而且两点之间只有一个棋子的时候
    //炮吃掉触摸点上的棋子
    if(killid != -1 && this->getStoneCount(xo,yo,x,y) == 1)
    {
        return true;
    }

    if(killid == -1 && this->getStoneCount(xo, yo, x, y) == 0) 
    {
        return true;
    }

    return false;
}


//兵的走棋规则
bool SceneGame::canMoveBing(int moveid, int x, int y)
{
     //兵的走棋规则：
    //1、一次走一格
    //2、前进一格后不能后退
    //3、过河后才可以左右移动

    //通过棋子的ID得到棋子
    Stone* s = _s[moveid];

    //获得将当前的位置
    int xo = s->getX();
    int yo = s->getY();

    //获得兵走的格数
    //(x,y)表示将走到的位置
    int xoff = abs(xo - x);
    int yoff = abs(yo - y);
    
    int d = xoff*10 + yoff;

    //走将的时候有两种情况
    //xoff=1, yoff=0：将向左或向右
    //xoff=0, yoff=1：将向前或向后
    if(d != 1 && d != 10)
    {
        return false;
    }

     //如果玩家的棋子是红棋
    if(_redSide == s->getRed())
    {
        //限制红色的兵不能后退
        if(y < yo)
        {
            return false;
        }

        //红色的兵没有过河不能左右移动
        if(yo <= 4 && y == yo)
        {
            return false;
        }
    }
    else//判断黑色的兵
    {
       //限制黑色的兵不能后退
        if(y > yo)
        {
            return false;
        }

         //黑色的兵没有过河不能左右移动
        if(yo >= 5 && y == yo)
        {
            return false;
        }
    }

    return true;
}


///计算(xo,yo)和(x,y)之间的棋子数
//如果棋子数为-1,表示(xo,yo)和(x,y)不在一条直线上
int SceneGame::getStoneCount(int xo, int yo, int x, int y)
{
    int ret = 0;//记录两点之间的棋子的个数

    //(xo,yo)和(x,y)不在同一条直线上
    if(xo != x && yo != y)
    {
        return -1;
    }

    //(xo,yo)和(x,y)在同一点上
    if(xo == x && yo == y)
    {
        return -1;
    }

    //两点在同一条竖线上
    if(xo == x)
    {
        //min为两个点中y坐标最小的点的y坐标
        int min = yo < y ? yo : y;

        //max为两个点中y坐标最大的点的y坐标
        int max = yo > y ? yo : y;

        //查找同一条竖线上两点之间的棋子数
        for(int yy=min+1; yy<max; yy++)
        {
            //当两点之间有棋子的时候
            if(getStone(x,yy) != -1)
            {
                ++ret;//棋子数加1
            }
        }
    }
    else//两点在同一条横线上yo == y
    {
        //min为两个点中x坐标最小的点的x坐标
        int min = xo < x ? xo : x;

        //max为两个点中x坐标最大的点的x坐标
        int max = xo > x ? xo : x;

        //查找同一条竖线上两点之间的棋子数
        for(int xx=min+1; xx<max; xx++)
        {
             //当两点之间有棋子的时候
            if(getStone(xx,y) != -1)
            {
                ++ret;//棋子数加1
            }
        }
    }

    //返回两点之间的棋子数
    return ret;
}

void SceneGame::updateAutoGo(float delay)
{  
	unschedule(schedule_selector(SceneGame::updateAutoGo));  
	if (!_redSide && _redTurn)
	{  
		aiGostep();  
	}  
}

void SceneGame::aiGostep()
{
	Step* aiStep = _ai->getOneMoveAction(1);
	if (aiStep != NULL)
	{
		moveStone(aiStep->_moveid, aiStep->_killid, aiStep->_xTo, aiStep->_yTo);
	}
}

void SceneGame::fakeMove(Step* step)
{
	int moveID = step->_moveid;
	int killID = step->_killid;
	int moveToX = step->_xTo;
	int moveToY = step->_yTo;
	if (canMove(moveID, killID, moveToX, moveToY))
	{
		Stone* moveStone = _s[moveID];
		moveStone->setX(moveToX);
		moveStone->setY(moveToY);
		if (killID != -1)
		{
			Stone* killStone = _s[killID];
			killStone->setDead(true);
		}
		this->_redTurn = !this->_redTurn;
	}
}

void SceneGame::unfakeMove(Step* step)
{
	int moveID = step->_moveid;
	int killID = step->_killid;
	int moveFromX = step->_xFrom;
	int moveFromY = step->_yFrom;
	Stone* moveStone = _s[moveID];
	moveStone->setX(moveFromX);
	moveStone->setY(moveFromY);
	if (killID != -1)
	{
		Stone* killStone = _s[killID];
		killStone->setDead(false);
	}
	this->_redTurn = !this->_redTurn;
}