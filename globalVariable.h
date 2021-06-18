#ifndef _GLOBAL_VARIABLE_
#define _GLOBAL_VARIABLE_

#include "cocos2d.h"
#include <string>
#include <vector>
#include <map>
#include "bullet.h"
#include "weapon.h"
#include "monster.h"

#define PI 3.14159f                         //暂时添加,用途未定

//宏定义方向
#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3
//依次表示右上左下方向
constexpr int DirectionX[4] = { 1, 0, -1, 0 };  
constexpr int DirectionY[4] = { 0, 1, 0, -1 };  

//宏定义画面时更新的移动方向
#define MvDirectionLR 0
#define MvDirectionUD 1

#define WIDTHOFWALL 40                      //代表墙壁贴图X向像素点数
#define HEIGHTOFWALL 60                     //代表墙壁贴图Y向像素点数

#define WIDTHOFFLOOR 40                     //代表地板贴图X向像素点数
#define HEIGHTOFFLOOR 40                    //代表地板贴图Y向像素点数

#define SIZEOFROOM 19                       //代表一个常规战斗房间X,Y方向默认包含贴图数量(包含地板和贴图)
#define SIZEOFCORRIDOR 7                    //代表走廊的默认宽度

#define CENTERDISTANCE 39*40                //代表两房间的默认标准中心距
#define SIZEOFCENTERDISTANCE 39             //代表两房间的中心距离的贴图数

//定义X,Y方向房间生成的最大数目
#define NumRoomX 5
#define NumRoomY 5  
//宏定义房间类型
#define TypeNormal 0
#define TypeBox 1                           //中心处生成道具
#define TypeBegin 2                         //将生成的第一个房间即房间延伸的初始房间定义为TypeBegin
#define TypeEnd 3                           //中心生成传送门
#define TypeBoss 4                          //关卡序号为5时生成以替代TypeEnd,Boss死亡后中心生成传送门
//拓展功能,后续update版本添加
//#define TypeStatue 5
//#define TypeStore 6

//宏定义关卡类型,击败Boss后切换关卡类型
#define levelTypeGreen 1
#define levelTypeIce 2
#define levelTypeFire 3
#define levelTypePoison 4

#define LR 0                                //定义走廊朝向左右
#define UD 1                                //定义走廊朝向上下

#define OPENED false                        //定义箱子已被打开
#define CLOSED true                         //定义箱子未被打开

#endif
