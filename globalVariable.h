#ifndef _GLOBAL_VARIABLE_
#define _GLOBAL_VARIABLE_

#include "cocos2d.h"
#include <string>
#include <vector>
#include <map>
#include "bullet.h"
#include "weapon.h"
#include "monster.h"

#define PI 3.14159f                         //��ʱ���,��;δ��

//�궨�巽��
#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3
//���α�ʾ�������·���
constexpr int DirectionX[4] = { 1, 0, -1, 0 };  
constexpr int DirectionY[4] = { 0, 1, 0, -1 };  

//�궨�廭��ʱ���µ��ƶ�����
#define MvDirectionLR 0
#define MvDirectionUD 1

#define WIDTHOFWALL 40                      //����ǽ����ͼX�����ص���
#define HEIGHTOFWALL 60                     //����ǽ����ͼY�����ص���

#define WIDTHOFFLOOR 40                     //����ذ���ͼX�����ص���
#define HEIGHTOFFLOOR 40                    //����ذ���ͼY�����ص���

#define SIZEOFROOM 19                       //����һ������ս������X,Y����Ĭ�ϰ�����ͼ����(�����ذ����ͼ)
#define SIZEOFCORRIDOR 7                    //�������ȵ�Ĭ�Ͽ��

#define CENTERDISTANCE 39*40                //�����������Ĭ�ϱ�׼���ľ�
#define SIZEOFCENTERDISTANCE 39             //��������������ľ������ͼ��

//����X,Y���򷿼����ɵ������Ŀ
#define NumRoomX 5
#define NumRoomY 5  
//�궨�巿������
#define TypeNormal 0
#define TypeBox 1                           //���Ĵ����ɵ���
#define TypeBegin 2                         //�����ɵĵ�һ�����伴��������ĳ�ʼ���䶨��ΪTypeBegin
#define TypeEnd 3                           //�������ɴ�����
#define TypeBoss 4                          //�ؿ����Ϊ5ʱ���������TypeEnd,Boss�������������ɴ�����
//��չ����,����update�汾���
//#define TypeStatue 5
//#define TypeStore 6

//�궨��ؿ�����,����Boss���л��ؿ�����
#define levelTypeGreen 1
#define levelTypeIce 2
#define levelTypeFire 3
#define levelTypePoison 4

#define LR 0                                //�������ȳ�������
#define UD 1                                //�������ȳ�������

#define OPENED false                        //���������ѱ���
#define CLOSED true                         //��������δ����

#endif
