
-- 游戏场景

function sceneGame()
	-- 创建并初始化场景 -----------------------------------------------------------------
	local scene = cc.Scene:create()

    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local origin = cc.Director:getInstance():getVisibleOrigin()

	-- 背景
	local bg = cc.Sprite:create("bg_table.jpg")
    bg:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)
	scene:addChild(bg)
	
	-- 菜单 ------------------------------------------------------------------------------
	local function menuCallbackBack()
		-- 返回菜单场景
		cc.Director:getInstance():replaceScene(sceneMenu())
	end
	
	local itemBack = createCustomMenuItem("item_back.png", "item_back.png")
	itemBack:setPosition(visibleSize.width/2+200, visibleSize.height-50)
    itemBack:registerScriptTapHandler(menuCallbackBack)
	local menuBack = cc.Menu:create(itemBack)
	menuBack:setPosition(origin)
	scene:addChild(menuBack)
	
	-- 游戏布景 --------------------------------------------------------------------------
	
	-- 玩家2头像和牌数
	
	local player2 = cc.Sprite:create("touxiang_nongmin.png")
	player2:setScale(0.8)
    player2:setPosition(origin.x + player2:getContentSize().width/2, origin.y + visibleSize.height - player2:getContentSize().height/2 + 10)
	scene:addChild(player2)
	
	-- 牌堆
	local pokerManager0 = IPokerManager:create()
	pokerManager0:setPosition(150,485)
	scene:addChild(pokerManager0, 1)
	
	-- 玩家3头像和牌数
	
	local player3 = cc.Sprite:create("touxiang_nongmin.png")
	player3:setScale(0.8)
    player3:setPosition(origin.x + visibleSize.width - player3:getContentSize().width/2, origin.y + visibleSize.height - player3:getContentSize().height/2 + 10)
	scene:addChild(player3)
	
	-- 牌堆
	local pokerManager1 = IPokerManager:create()
	pokerManager1:setPosition(800,485)
	scene:addChild(pokerManager1, 1)
	
	-- 玩家头像
		
	local player1 = cc.Sprite:create("touxiang_dizhu.png")
	player1:setScale(0.8)
    player1:setPosition(origin.x + player1:getContentSize().width/2, origin.y + player1:getContentSize().height/2 + 200 - 20)
	scene:addChild(player1)
	
	-- 牌堆
	local pokerManager = PokerManager:create()
	pokerManager:setPosition(visibleSize.width/2,visibleSize.height/6)
	scene:addChild(pokerManager, 1)
	
	-- 游戏菜单 ------------------------------------------------------------------------------
	local function menuCallbackTishi()
		print("提示")
	end
	
	local function menuCallbackChongxuan()
		print("重选")
	end
	
	local function menuCallbackBuchu()
		print("不出")
	end
	
	local function menuCallbackChupai()
		print("出牌")
		pokerManager:chuPai()
		pokerManager0:chuPai()
		pokerManager1:chuPai()
	end
	
	local itemTishi = createCustomMenuItem("item_tishi.png", "item_tishi_d.png")
	itemTishi:setPosition(-200 , 0)
    itemTishi:registerScriptTapHandler(menuCallbackTishi)
	
	local itemChongxuan = createCustomMenuItem("item_chongxuan.png", "item_chongxuan_d.png")
	itemChongxuan:setPosition(0, 0)
    itemChongxuan:registerScriptTapHandler(menuCallbackChongxuan)
	
	local itemBuchu = createCustomMenuItem("item_buchu.png", "item_buchu_d.png")
	itemBuchu:setPosition(200, 0)
    itemBuchu:registerScriptTapHandler(menuCallbackBuchu)
	
	local itemChupai = createCustomMenuItem("item_chupai.png", "item_chupai_d.png")
	itemChupai:setPosition(400, 0)
    itemChupai:registerScriptTapHandler(menuCallbackChupai)
	
	local menuGame = cc.Menu:create(itemTishi, itemChongxuan, itemBuchu, itemChupai)
	menuGame:setPosition(origin.x + visibleSize.width / 2 - 50, origin.y + visibleSize.height / 2 - 50)
	scene:addChild(menuGame)
	menuGame:setVisible(false)
	
	-- 准备菜单 ------------------------------------------------------------------------------
	local menuZhunbei
	
	local function menuCallbackZhunbei()
		
		-- 准备开始游戏
		menuGame:setVisible(true)
		menuZhunbei:setVisible(false)
		
		-- 发牌
		local schedulerID = nil  
		
		local function callbackDealer()
			if pokerManager:dealer()==false then
				-- 停止发牌
				cc.Director:getInstance():getScheduler():unscheduleScriptEntry(schedulerID)   
			end
			
			pokerManager0:dealer()
			pokerManager1:dealer()
		end

		schedulerID = cc.Director:getInstance():getScheduler():scheduleScriptFunc(callbackDealer,0.05,false)
	end
	
	local itemZhunbei = createCustomMenuItem("item_zhunbei.png", "item_zhunbei.png")
	itemZhunbei:setPosition(visibleSize.width/2, visibleSize.height/2)
    itemZhunbei:registerScriptTapHandler(menuCallbackZhunbei)
	menuZhunbei = cc.Menu:create(itemZhunbei)
	menuZhunbei:setPosition(origin)
	scene:addChild(menuZhunbei)
	
	-- 返回场景 -------------------------------------------------------------------------
    return scene
end