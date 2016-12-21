#include "lua_myclass_auto.hpp"
#include "PokerManager.h"
#include "Poker.h"
#include "PokerExhibitionZone.h"
#include "IPokerManager.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_myclass_Poker_onTouchMoved(lua_State* tolua_S)
{
    int argc = 0;
    Poker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Poker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_Poker_onTouchMoved'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_onTouchMoved'", nullptr);
            return 0;
        }
        cobj->onTouchMoved(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "Poker:onTouchMoved",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_onTouchMoved'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_Poker_onTouchEnded(lua_State* tolua_S)
{
    int argc = 0;
    Poker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Poker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_Poker_onTouchEnded'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_onTouchEnded'", nullptr);
            return 0;
        }
        cobj->onTouchEnded(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "Poker:onTouchEnded",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_onTouchEnded'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_Poker_getInfo(lua_State* tolua_S)
{
    int argc = 0;
    Poker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Poker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_Poker_getInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_getInfo'", nullptr);
            return 0;
        }
        PokerInfo ret = cobj->getInfo();
        #pragma warning NO CONVERSION FROM NATIVE FOR PokerInfo;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "Poker:getInfo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_getInfo'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_Poker_getRect(lua_State* tolua_S)
{
    int argc = 0;
    Poker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Poker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_Poker_getRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_getRect'", nullptr);
            return 0;
        }
        cocos2d::Rect ret = cobj->getRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "Poker:getRect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_getRect'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_Poker_onTouchCancelled(lua_State* tolua_S)
{
    int argc = 0;
    Poker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Poker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_Poker_onTouchCancelled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_onTouchCancelled'", nullptr);
            return 0;
        }
        cobj->onTouchCancelled(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "Poker:onTouchCancelled",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_onTouchCancelled'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_Poker_onTouchBegan(lua_State* tolua_S)
{
    int argc = 0;
    Poker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Poker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_Poker_onTouchBegan'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Touch* arg0;
        cocos2d::Event* arg1;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);

        ok &= luaval_to_object<cocos2d::Event>(tolua_S, 3, "cc.Event",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_onTouchBegan'", nullptr);
            return 0;
        }
        bool ret = cobj->onTouchBegan(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "Poker:onTouchBegan",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_onTouchBegan'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_Poker_isSelected(lua_State* tolua_S)
{
    int argc = 0;
    Poker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Poker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_Poker_isSelected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_isSelected'", nullptr);
            return 0;
        }
        bool ret = cobj->isSelected();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "Poker:isSelected",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_isSelected'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_Poker_init(lua_State* tolua_S)
{
    int argc = 0;
    Poker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Poker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_Poker_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        PokerInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR PokerInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "Poker:init",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_init'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_Poker_click(lua_State* tolua_S)
{
    int argc = 0;
    Poker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Poker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_Poker_click'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_click'", nullptr);
            return 0;
        }
        cobj->click();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "Poker:click",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_click'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_Poker_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"Poker",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        PokerInfo arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR PokerInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_Poker_create'", nullptr);
            return 0;
        }
        Poker* ret = Poker::create(arg0);
        object_to_luaval<Poker>(tolua_S, "Poker",(Poker*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "Poker:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_Poker_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_myclass_Poker_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Poker)");
    return 0;
}

int lua_register_myclass_Poker(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"Poker");
    tolua_cclass(tolua_S,"Poker","Poker","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"Poker");
        tolua_function(tolua_S,"onTouchMoved",lua_myclass_Poker_onTouchMoved);
        tolua_function(tolua_S,"onTouchEnded",lua_myclass_Poker_onTouchEnded);
        tolua_function(tolua_S,"getInfo",lua_myclass_Poker_getInfo);
        tolua_function(tolua_S,"getRect",lua_myclass_Poker_getRect);
        tolua_function(tolua_S,"onTouchCancelled",lua_myclass_Poker_onTouchCancelled);
        tolua_function(tolua_S,"onTouchBegan",lua_myclass_Poker_onTouchBegan);
        tolua_function(tolua_S,"isSelected",lua_myclass_Poker_isSelected);
        tolua_function(tolua_S,"init",lua_myclass_Poker_init);
        tolua_function(tolua_S,"click",lua_myclass_Poker_click);
        tolua_function(tolua_S,"create", lua_myclass_Poker_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Poker).name();
    g_luaType[typeName] = "Poker";
    g_typeCast["Poker"] = "Poker";
    return 1;
}

int lua_myclass_PokerExhibitionZone_init(lua_State* tolua_S)
{
    int argc = 0;
    PokerExhibitionZone* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PokerExhibitionZone",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PokerExhibitionZone*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_PokerExhibitionZone_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_PokerExhibitionZone_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PokerExhibitionZone:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_PokerExhibitionZone_init'.",&tolua_err);
#endif

    return 0;
}

int lua_myclass_PokerExhibitionZone_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"PokerExhibitionZone",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_PokerExhibitionZone_create'", nullptr);
            return 0;
        }
        PokerExhibitionZone* ret = PokerExhibitionZone::create();
        object_to_luaval<PokerExhibitionZone>(tolua_S, "PokerExhibitionZone",(PokerExhibitionZone*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "PokerExhibitionZone:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_PokerExhibitionZone_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_myclass_PokerExhibitionZone_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PokerExhibitionZone)");
    return 0;
}

int lua_register_myclass_PokerExhibitionZone(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"PokerExhibitionZone");
    tolua_cclass(tolua_S,"PokerExhibitionZone","PokerExhibitionZone","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"PokerExhibitionZone");
        tolua_function(tolua_S,"init",lua_myclass_PokerExhibitionZone_init);
        tolua_function(tolua_S,"create", lua_myclass_PokerExhibitionZone_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(PokerExhibitionZone).name();
    g_luaType[typeName] = "PokerExhibitionZone";
    g_typeCast["PokerExhibitionZone"] = "PokerExhibitionZone";
    return 1;
}

int lua_myclass_PokerManager_updatePokers(lua_State* tolua_S)
{
    int argc = 0;
    PokerManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PokerManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PokerManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_PokerManager_updatePokers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_PokerManager_updatePokers'", nullptr);
            return 0;
        }
        cobj->updatePokers();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PokerManager:updatePokers",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_PokerManager_updatePokers'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_PokerManager_init(lua_State* tolua_S)
{
    int argc = 0;
    PokerManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PokerManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PokerManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_PokerManager_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_PokerManager_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PokerManager:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_PokerManager_init'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_PokerManager_dealer(lua_State* tolua_S)
{
    int argc = 0;
    PokerManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PokerManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PokerManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_PokerManager_dealer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_PokerManager_dealer'", nullptr);
            return 0;
        }
        bool ret = cobj->dealer();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PokerManager:dealer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_PokerManager_dealer'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_PokerManager_chuPai(lua_State* tolua_S)
{
    int argc = 0;
    PokerManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"PokerManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (PokerManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_PokerManager_chuPai'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_PokerManager_chuPai'", nullptr);
            return 0;
        }
        cobj->chuPai();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "PokerManager:chuPai",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_PokerManager_chuPai'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_PokerManager_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"PokerManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_PokerManager_create'", nullptr);
            return 0;
        }
        PokerManager* ret = PokerManager::create();
        object_to_luaval<PokerManager>(tolua_S, "PokerManager",(PokerManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "PokerManager:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_PokerManager_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_myclass_PokerManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PokerManager)");
    return 0;
}

int lua_register_myclass_PokerManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"PokerManager");
    tolua_cclass(tolua_S,"PokerManager","PokerManager","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"PokerManager");
        tolua_function(tolua_S,"updatePokers",lua_myclass_PokerManager_updatePokers);
        tolua_function(tolua_S,"init",lua_myclass_PokerManager_init);
        tolua_function(tolua_S,"dealer",lua_myclass_PokerManager_dealer);
        tolua_function(tolua_S,"chuPai",lua_myclass_PokerManager_chuPai);
        tolua_function(tolua_S,"create", lua_myclass_PokerManager_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(PokerManager).name();
    g_luaType[typeName] = "PokerManager";
    g_typeCast["PokerManager"] = "PokerManager";
    return 1;
}

int lua_myclass_IPokerManager_init(lua_State* tolua_S)
{
    int argc = 0;
    IPokerManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"IPokerManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (IPokerManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_IPokerManager_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_IPokerManager_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "IPokerManager:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_IPokerManager_init'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_IPokerManager_dealer(lua_State* tolua_S)
{
    int argc = 0;
    IPokerManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"IPokerManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (IPokerManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_IPokerManager_dealer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_IPokerManager_dealer'", nullptr);
            return 0;
        }
        bool ret = cobj->dealer();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "IPokerManager:dealer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_IPokerManager_dealer'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_IPokerManager_chuPai(lua_State* tolua_S)
{
    int argc = 0;
    IPokerManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"IPokerManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (IPokerManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_myclass_IPokerManager_chuPai'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_IPokerManager_chuPai'", nullptr);
            return 0;
        }
        cobj->chuPai();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "IPokerManager:chuPai",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_IPokerManager_chuPai'.",&tolua_err);
#endif

    return 0;
}
int lua_myclass_IPokerManager_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"IPokerManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_myclass_IPokerManager_create'", nullptr);
            return 0;
        }
        IPokerManager* ret = IPokerManager::create();
        object_to_luaval<IPokerManager>(tolua_S, "IPokerManager",(IPokerManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "IPokerManager:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_myclass_IPokerManager_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_myclass_IPokerManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (IPokerManager)");
    return 0;
}

int lua_register_myclass_IPokerManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"IPokerManager");
    tolua_cclass(tolua_S,"IPokerManager","IPokerManager","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"IPokerManager");
        tolua_function(tolua_S,"init",lua_myclass_IPokerManager_init);
        tolua_function(tolua_S,"dealer",lua_myclass_IPokerManager_dealer);
        tolua_function(tolua_S,"chuPai",lua_myclass_IPokerManager_chuPai);
        tolua_function(tolua_S,"create", lua_myclass_IPokerManager_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(IPokerManager).name();
    g_luaType[typeName] = "IPokerManager";
    g_typeCast["IPokerManager"] = "IPokerManager";
    return 1;
}
TOLUA_API int register_all_myclass(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_myclass_Poker(tolua_S);
	lua_register_myclass_PokerManager(tolua_S);
	lua_register_myclass_PokerExhibitionZone(tolua_S);
	lua_register_myclass_IPokerManager(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

