/**********************************************************************
@file		AppMacros.h
@brief		��Ϸ�ĺ궨���ļ�
@author		Ray1024
@date		2016-9-22
***********************************************************************/

#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

//----------------------------------------------------------
// ��ͬƽ̨�ĳߴ綨��
//----------------------------------------------------------

//#define ANDROID_MI3		// ��ֲ��С��3ƽ̨

#ifdef ANDROID_MI3

// �ƶ��豸�ֱ���
#define		SCALE_FACTOR	1.f
#define		WINSIZE_W		1080
#define		WINSIZE_H		1920

#else

// ��Ϸ��Ƴߴ�
#define		SCALE_FACTOR		2.4f
#define		WINSIZE_W			450
#define		WINSIZE_H			800

#endif // ANDROID_MI3
//----------------------------------------------------------

#endif //__APPMACROS_H__