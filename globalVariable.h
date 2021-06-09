#ifndef _GLOBAL_VARIABLE_
#define _GLOBAL_VARIABLE_

#include "cocos2d.h"
#include <string>
#include <vector>
#include <map>
#include "bullet.h"
#include "weapon.h"
#include "RangedWeapon.h"

#define PI 3.14159f                         //暂时添加,用途未定

#define WIDTHOFWALL 40                      //代表墙壁贴图X向像素点数
#define HEIGHTOFWALL 60                     //代表墙壁贴图Y向像素点数

#define WIDTHOFFLOOR 40                     //代表地板贴图X向像素点数
#define HEIGHTOFFLOOR 40                    //代表地板贴图Y向像素点数

#define SIZEOFROOM 20                       //代表一个常规房间默认包含贴图数量(包含地板和贴图)

//宏定义房间类型
#define TypeNormal 0
#define TypeBox 1                           //中心处生成道具
#define TypeBegin 2                         //将生成的第一个房间即房间延伸的初始房间定义为TypeBegin
#define TypeEnd 3                           //中心生成传送门
#define TypeBoss 4                          //关卡序号为5时生成以替代TypeEnd,Boss死亡后中心生成传送门
//拓展功能,后续update版本添加
//#define TypeStatue 5
//#define TypeStore 6

#endif
