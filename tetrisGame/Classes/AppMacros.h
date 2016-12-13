/**********************************************************************
@file		AppMacros.h
@brief		游戏的宏定义文件
@author		Ray1024
@date		2016-9-22
***********************************************************************/

#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

//----------------------------------------------------------
// 不同平台的尺寸定义
//----------------------------------------------------------

//#define ANDROID_MI3		// 移植到小米3平台

#ifdef ANDROID_MI3

// 移动设备分辨率
#define		SCALE_FACTOR	1.f
#define		WINSIZE_W		1080
#define		WINSIZE_H		1920

#else

// 游戏设计尺寸
#define		SCALE_FACTOR		2.4f
#define		WINSIZE_W			450
#define		WINSIZE_H			800

#endif // ANDROID_MI3
//----------------------------------------------------------

#endif //__APPMACROS_H__