
-- 创建自定义菜单项（菜单选中的图片为正常图片加灰）
-- 参数1	正常图片
-- 参数2	不可用图片（这个参数必须有，如果不添加不可用图片，就填正常图片）

function createCustomMenuItem(str, strDisable)
	local image = cc.Sprite:create(str)
	image:setColor(cc.c3b(100,100,100))
	local item = cc.MenuItemSprite:create(cc.Sprite:create(str), image, cc.Sprite:create(strDisable))
	
	return item
end

-- 菜单场景

function sceneMenu()
	-- 创建并初始化场景 -----------------------------------------------------------------
	local scene = cc.Scene:create()

    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local origin = cc.Director:getInstance():getVisibleOrigin()

	-- 背景
	local bg = cc.Sprite:create("bg.jpg")
    bg:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)
	scene:addChild(bg)
	
	local logo = cc.Sprite:create("hall_loading.png")
    logo:setPosition(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 2)
	scene:addChild(logo)
	
	-- 创建菜单 -----------------------------------------------------------------------
	
	local function menuCallbackBegin()
		-- 开始游戏
		cc.Director:getInstance():replaceScene(sceneGame())
	end

	local function menuCallbackExit()
		-- 退出游戏
		cc.Director:getInstance():endToLua()
	end
	
	
	local itemBegin = createCustomMenuItem("item_begin.png", "item_begin.png")
	itemBegin:setPosition(0, 100)
    itemBegin:registerScriptTapHandler(menuCallbackBegin)
	
	local itemExit = createCustomMenuItem("item_exit.png", "item_exit.png")
	itemExit:setPosition(0, -100)
    itemExit:registerScriptTapHandler(menuCallbackExit)
	
	local menuMain = cc.Menu:create(itemBegin, itemExit)
	menuMain:setPosition(origin.x + visibleSize.width / 4 * 3, origin.y + visibleSize.height / 2)
	scene:addChild(menuMain)
	
	-- 返回场景 ------------------------------------------------------------------------
    return scene
end