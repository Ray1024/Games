/**********************************************************************
@file		AppCommon.h
@brief		游戏的宏定义文件
@author		Ray1024
@date		2016-12-21
***********************************************************************/

#ifndef __APPCOMMON_H__
#define __APPCOMMON_H__

#include "cocos2d.h"

// 创建自定义菜单项
cocos2d::MenuItemSprite* createCustomMenuItem(const std::string& normalImage, const std::string& disabledImage);

#endif //__APPCOMMON_H__