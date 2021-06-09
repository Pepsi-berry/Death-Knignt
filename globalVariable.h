#ifndef _GLOBAL_VARIABLE_
#define _GLOBAL_VARIABLE_

#include "cocos2d.h"
#include <string>
#include <vector>
#include <map>
#include "bullet.h"
#include "weapon.h"
#include "RangedWeapon.h"

#define PI 3.14159f                         //��ʱ���,��;δ��

#define WIDTHOFWALL 40                      //����ǽ����ͼX�����ص���
#define HEIGHTOFWALL 60                     //����ǽ����ͼY�����ص���

#define WIDTHOFFLOOR 40                     //����ذ���ͼX�����ص���
#define HEIGHTOFFLOOR 40                    //����ذ���ͼY�����ص���

#define SIZEOFROOM 20                       //����һ�����淿��Ĭ�ϰ�����ͼ����(�����ذ����ͼ)

//�궨�巿������
#define TypeNormal 0
#define TypeBox 1                           //���Ĵ����ɵ���
#define TypeBegin 2                         //�����ɵĵ�һ�����伴��������ĳ�ʼ���䶨��ΪTypeBegin
#define TypeEnd 3                           //�������ɴ�����
#define TypeBoss 4                          //�ؿ����Ϊ5ʱ���������TypeEnd,Boss�������������ɴ�����
//��չ����,����update�汾���
//#define TypeStatue 5
//#define TypeStore 6

#endif
