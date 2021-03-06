/**********************************************************************
@file		AppMacros.h
@brief		游戏的宏定义文件
@author		Jianlei Guo
@date		2016-9-22
***********************************************************************/

#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

//不同平台的尺寸定义----------------------------------------

#define ANDROID_MI3		// 移植到小米3平台

#ifdef ANDROID_MI3

// 缩放比例
#define		SCALE_FACTOR	0.5f
#define		WINSIZE_W		1080
#define		WINSIZE_H		1920

#else

// 缩放比例
#define		SCALE_FACTOR		2.f//1.f
#define		WINSIZE_W			270//540
#define		WINSIZE_H			480//960

#endif // ANDROID_MI3
//----------------------------------------------------------


#endif /* __APPMACROS_H__ */
