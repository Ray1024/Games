
cc.FileUtils:getInstance():addSearchPath("src")
cc.FileUtils:getInstance():addSearchPath("res")

-- CC_USE_DEPRECATED_API = true
require "cocos.init"
require "sceneMenu"
require "sceneGame"

-- cclog
cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
    return msg
end

local function main()
    collectgarbage("collect")
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)

    -- 初始化导演和窗口------------------------------------------------------------
    local director = cc.Director:getInstance()
    local glview = director:getOpenGLView()
    if nil == glview then
        glview = cc.GLViewImpl:createWithRect("CocosLuaTests", cc.rect(0,0,960,540))
        director:setOpenGLView(glview)
    end

    director:setDisplayStats(true)
    director:setAnimationInterval(1.0 / 60)

    -- 加载游戏资源----------------------------------------------------------------

	local cache  = cc.SpriteFrameCache:getInstance()
    cache:addSpriteFrames("poker_b.plist","poker_b.png")
	
    -- 运行 -----------------------------------------------------------------------
    local scene = sceneMenu()
	
    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(scene)
    else
        cc.Director:getInstance():runWithScene(scene)
    end

end


local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    error(msg)
end
