/*
 * graphics.h
 *
 *  Created on: 2016年4月9日
 *      Author: yami
 */

/**
 * @file	graphics.h
 * @author	yami
 * @date	2016年4月9日
 * @brief
 * 
 */

#ifndef SRC_GRAPHICS_H_
#define SRC_GRAPHICS_H_

#include <mixmworld.h>





typedef struct Graphics Graphics;
typedef struct GraphicsFPtr GraphicsFPtr;
struct GraphicsFPtr{
	void*	r;
	void	(*free)(void*v);
	int		(*GetWidth)(void*v);
	int		(*GetHeight)(void*v);
	int		(*Draw)(void*v,Rect*src,Rect*dst);
	int		(*Draw_dst)(void*v,Rect*dst);
	int		(*Draw_dst_xywh)(void*v,int x,int y,int w,int h);
	int		(*Draw_copy)(void*v,int x,int y);
};

typedef union{
	Graphics		*graphics;
	GraphicsFPtr	**graphicsFPtr;
}GraphicsIface;


INLINE int	Graphics_Draw(Graphics*self,Rect*src,Rect*dst);
INLINE int	Graphics_Draw_dst(Graphics*self,Rect*dst);
INLINE int	Graphics_Draw_dst_xywh(Graphics*self,int x,int y,int w,int h);
INLINE int	Graphics_Draw_copy(Graphics*self,int x,int y);
INLINE int	Graphics_GetWidth(Graphics*self);
INLINE int	Graphics_GetHeight(Graphics*self);




//========================================================================
//函数实现
INLINE int	Graphics_Draw(Graphics*self,Rect*src,Rect*dst){
	GraphicsIface	i;
	i.graphics	=	self;
	return i.graphicsFPtr[0]->Draw(self,src,dst);
}
INLINE int	Graphics_Draw_dst(Graphics*self,Rect*dst){
	GraphicsIface	i;
	i.graphics	=	self;
	return i.graphicsFPtr[0]->Draw_dst(self,dst);
}
INLINE int	Graphics_Draw_dst_xywh(Graphics*self,int x,int y,int w,int h){
	GraphicsIface	i;
	i.graphics	=	self;
	return i.graphicsFPtr[0]->Draw_dst_xywh(self,x,y,w,h);
}

INLINE int	Graphics_GetWidth(Graphics*self){
	GraphicsIface	i;
	i.graphics	=	self;
	GraphicsFPtr	*fptr = i.graphicsFPtr[0];
	return fptr->GetWidth(self);
}
INLINE int	Graphics_GetHeight(Graphics*self){
	GraphicsIface	i;
	i.graphics	=	self;
	return i.graphicsFPtr[0]->GetHeight(self);
}

INLINE int	Graphics_Draw_copy(Graphics*self,int x,int y){
	GraphicsIface	i;
	i.graphics	=	self;
	return i.graphicsFPtr[0]->Draw_copy(self,x,y);
}

#endif /* SRC_GRAPHICS_H_ */
