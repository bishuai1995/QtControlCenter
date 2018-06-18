#pragma once
#include <memory>
#include <string.h>
#include "../QtControl/include/develop_interface.h"
#include "../QtControl/log/log_deffine.h"
#include "Base/myhelper.h"
#include "Base/RunTime.h"
#include "qextserialport_win/qextserialport.h"
#include "QPortControl.h"


//����
#define  WantOpenDoor      "3A 30 32 30 36 31 32 30 33 30 30 30 31 45 32 0D 0A"
#define  StartOpenDoor     "3A 30 32 30 36 31 32 30 34 30 30 30 31 45 31 0D 0A"
#define  AskOpenDoor       "3A 30 32 30 33 31 32 30 34 30 30 30 31 45 34 0D 0A"
#define OpenDoorFail       "3A 30 32 30 33 30 32 30 30 30 31 46 38 0D 0A"
#define OpenDoorSucess     "3A 30 32 30 33 30 32 30 30 30 30 46 39 0D 0A"

//����
#define  WantDoorClose     "3A 30 32 30 36 31 32 30 33 30 30 30 30 45 33 0D 0A"
#define  StartCloseDoor    "3A 30 32 30 36 31 32 30 34 30 30 30 31 45 31 0D 0A"
#define  AskCloseDoor      "3A 30 32 30 33 31 32 30 34 30 30 30 31 45 34 0D 0A"
#define  CloseDoorFail     "3A 30 32 30 33 30 32 30 30 30 31 46 38 0D 0A"
#define  CloseDoorSucess   "3A 30 32 30 33 30 32 30 30 30 30 46 39 0D 0A"

//��ס����
#define WantSuckTray       "3A 30 32 30 36 31 32 30 37 30 30 30 31 44 45 0D 0A"
#define StartSuckTray      "3A 30 32 30 36 31 32 30 38 30 30 30 31 44 44 0D 0A"
#define AskSuckTray        "3A 30 32 30 33 31 32 30 38 30 30 30 31 45 30 0D 0A"
#define SuckTrayFail       "3A 30 32 30 33 30 32 30 30 30 31 46 38 0D 0A"
#define SuckTraySucess     "3A 30 32 30 33 30 32 30 30 30 30 46 39 0D 0A"

//�ſ�����
#define WantDropTray      "3A 30 32 30 36 31 32 30 37 30 30 30 30 44 46 0D 0A"
#define StartDropTray     "3A 30 32 30 36 31 32 30 38 30 30 30 31 44 44 0D 0A"
#define AskDropTray       "3A 30 32 30 33 31 32 30 38 30 30 30 31 45 30 0D 0A"
#define DropTrayFail      "3A 30 32 30 33 30 32 30 30 30 31 46 38 0D 0A"
#define DropTraySucess    "3A 30 32 30 33 30 32 30 30 30 30 46 39 0D 0A"

//��ȡ����
#define  WantPushGoods     "3A 30 32 30 36 31 32 30 35 30 30 30 31 45 30 0D 0A"
#define  StartPushGoods    "3A 30 32 30 36 31 32 30 36 30 30 30 31 44 46 0D 0A"
#define  AskPushGoods      "3A 30 32 30 33 31 32 30 36 30 30 30 31 45 32 0D0A"
#define  PushGoodsFail     "3A 30 32 30 33 30 32 30 30 30 31 46 38 0D 0A"
#define  PushGoodsSucess   "3A 30 32 30 33 30 32 30 30 30 30 46 39 0D 0A"

//���͵�λ
#define  WantGetGoods      "3A 30 32 30 36 31 32 30 35 30 30 30 30 45 31 0D 0A"
#define  StartGetGoods     "3A 30 32 30 36 31 32 30 36 30 30 30 31 44 46 0D 0A"
#define  AskGetGoods       "3A 30 32 30 33 31 32 30 36 30 30 30 31 45 32 0D0A"
#define  GetGoodsFail      "3A 30 32 30 33 30 32 30 30 30 31 46 38 0D 0A"
#define  GetGoodsSucess    "3A 30 32 30 33 30 32 30 30 30 30 46 39 0D 0A"



//�˶������ж���
#define WantMoveToX      "3A 30 32 30 36 31 32 30 30 30 30"
#define WantMoveToY      "3A 30 32 30 36 31 32 30 31 30 30"

#define CountX           "02 06 12 00 00"
#define CountY           "02 06 12 01 00"

#define StartMove        "3A 30 32 30 36 31 32 30 32 30 30 30 31 45 33 0D 0A"
#define AskMove          "3A 30 32 30 33 31 32 30 32 30 30 30 31 45 36 0D 0A"
#define MoveFail         "3A 30 32 30 33 30 32 30 30 30 31 46 38 0D 0A"
#define MoveSucess       "3A 30 32 30 33 30 32 30 30 30 30 46 39 0D 0A"

#define MOVEZEROROW      "3A 30 32 30 36 31 32 30 30 30 30 30 30 45 36 0D 0A"
#define MOVEZEROCOLUMN   "3A 30 32 30 36 31 32 30 31 30 30 30 30 45 35 0D 0A"

#define  MOVEEND         "0D 0A"

#define   MAXCOLUMN  8
#define   MAXROW     20

#define   ADDROW       5
#define   MAXNULLTRAY  5

class AppInfo
{
public:
	AppInfo()
	{
		savePoint.setX(0);
		savePoint.setY(0);
		saveQRNum = 0;
		saveHeight = 0;
		saveWeight = 0;
		phoneNum = 0;
		userName = "";
	};
public:
	QPoint savePoint;  //�����λ��
	int    saveQRNum;	//����Ķ�ά������	
	int    saveHeight;//����ĸ߶�
	int    saveWeight;//���������
	long   phoneNum;
	std::string userName;

	//int    isdetele;
};



//��̬��
#ifdef _DEBUG

#pragma comment(lib, "../QtControl/lib/vbar.lib")


#else

#pragma comment(lib, "../QtControl/lib/vbar.lib")

#endif
