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
#define  WantDoorOpen      "3A 02 06 12 03 00 01 E2 0D0A"
#define  StartOpenDoor     "3A 02 06 12 04 00 01 E1 0D0A"
#define  AskOpenDoor       "3A 02 03 12 04 00 01 E4 0D0A"
#define  OpenDoorSucess    "3A 02 03 12 04 00 00 E5 0D0A"

//����
#define  WantDoorClose     "3A 02 06 12 03 00 00 E3 ODOA"
#define  StartCloseDoor    "3A 02 06 12 04 00 01 E1 0D0A"
#define  AskCloseDoor      "3A 02 03 12 04 00 01 E4 0D0A"
#define  CloseDoorSucess   "3A 02 03 12 04 00 00 E5 0D0A"

//��ס����
#define WantSuckTray    "3A 02 06 12 07 00 01"
#define StartSuckTray   "3A 02 06 12 08 00 01"
#define AskSuckTray    "3A 02 03 12 08 00 01"
#define SuckTraySucess   "3A 02 03 12 08 00 00"

//�ſ�����
#define WantDropTray    "3A 02 06 12 07 00 00 DF 0D0A"
#define StartDropTray   "3A 02 06 12 08 00 01 DD 0D0A"
#define AskDropTray     "3A 02 03 12 08 00 01 E0 0D0A"
#define DropTraySucess  "3A 02 03 12 08 00 00 E1 0D0A"

//��ȡ����
#define WantGetGoods    "3A 02 06 12 05 00 01"
#define StartGetGoods   "3A 02 06 12 06 00 01"
#define AskGetGoods     "3A 02 03 12 06 00 01"
#define GetGoodsSucess   "3A 02 03 12 06 00 00"


//�˶������ж���
#define WantMoveToX    "3A 01 06 12 00 00"
#define WantMoveToY    "3A 01 06 12 01 00"

#define StartMove   "3A 02 06 12 02 00 01 E3 0D0A"
#define AskMove     "3A 02 03 12 02 00 01 E6 0D0A"
#define MoveSucess  "3A 02 03 12 02 00 00 E7 0D0A"


//���͵�λ
#define WantPushGoods    "3A 02 06 12 05 00 00 E1 0D0A"
#define StartPushGoods   "3A 02 06 12 06 00 01 DF 0D0A"
#define AsktPushGoods    "3A 02 03 12 06 00 01 E2 0DOA"
#define PushGoodsSucess  "3A 02 03 12 06 00 00 E3 0a0a"



#define   MAXCOLUMN  8
#define   MAXROW     15

#define   ADDROW       5
#define   MAXNULLTRAY  0

class AppInfo
{
public:
	QPoint savePoint;  //�����λ��
	//int    saveRow;
	//int    saveColumn;
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
