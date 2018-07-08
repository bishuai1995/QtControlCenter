#include "QPortControl.h"
#include <QMessageBox>
QPortControl::QPortControl(QObject *parent)
	: QObject(parent)
{
	connect(gbl485SerialPort, SIGNAL(sig_ReadData(QString)), this, SLOT(slot_ReadData(QString)));

	connect(gbl232SerialPort, SIGNAL(sig_ReadData(QString)), this, SLOT(slot_232ReadData(QString)));

	connect(gbl485HeightPort, SIGNAL(sig_ReadData(QString)), this, SLOT(slot_heightReadData(QString)));

}

QPortControl::~QPortControl()
{
}

void QPortControl::slot_ReadData(QString strRecevice)
{
	LOG_INFO("slot_ReadData =[%s]", strRecevice.toStdString().c_str());




	//��λ���յ���������
	if (strRecevice.toUpper() == WantOpenDoor)
	{
		//��λ�����Ϳ�ʼִ�п��Ŷ���
		m_Action = Action_OpenDoor;
		gbl485SerialPort->AddTask(StartOpenDoor);
		return;
	}
	//��λ�����Ϳ�ʼִ�п��Ŷ���
	if (strRecevice.toUpper() == StartOpenDoor && m_Action == Action_OpenDoor)
	{		
		gbl485SerialPort->AddTask(AskOpenDoor);
		return;
	}
	//��λ�����Ϳ�ʼִ�п��Ŷ���
	if (strRecevice.toUpper() == OpenDoorFail && m_Action == Action_OpenDoor)
	{
		gbl485SerialPort->AddTask(AskOpenDoor);
		return;
	}
	//��λ���յ����ųɹ����ź�
	if (strRecevice.toUpper() == OpenDoorSucess&& m_Action == Action_OpenDoor)
	{
		m_Action = Action_Null;
		emit sig_OpendoorFinish();	
		return;
	}

	/**********����*****************/
	//��λ���յ���������
	if (strRecevice.toUpper() == WantDoorClose)
	{
		//��λ�����Ϳ�ʼִ�й��Ŷ���
		m_Action = Action_CloseDoor;
		gbl485SerialPort->AddTask(StartCloseDoor);
		return;
	}
	//��λ��ѯ���Ƿ���ɹ����Ŷ�����
	if (strRecevice.toUpper() == StartCloseDoor && m_Action == Action_CloseDoor)
	{
		gbl485SerialPort->AddTask(AskCloseDoor);
		return;
	}
	//��λ�����Ϳ�ʼִ�й��Ŷ���
	if (strRecevice.toUpper() == CloseDoorFail && m_Action == Action_CloseDoor)
	{
		gbl485SerialPort->AddTask(AskCloseDoor);
		return;
	}
	//��λ���յ����ųɹ����ź�
	if (strRecevice.toUpper() == CloseDoorSucess && m_Action == Action_CloseDoor)
	{
		m_Action = Action_Null;
		emit sig_ClosedoorFinish();	
		return;
	}

	/**********��ס����*****************/
	//��λ���յ���ס��������
	if (strRecevice.toUpper() == WantSuckTray)
	{
		m_Action = Action_SuckTray;
		//��λ������ִ�е������ס���̿�ʼ����
		gbl485SerialPort->AddTask(StartSuckTray);
		return;
	}	
	if (strRecevice.toUpper() == StartSuckTray && m_Action == Action_SuckTray)
	{
		//��λ����ȡ������̶����Ƿ�ִ����ɣ�
		gbl485SerialPort->AddTask(AskSuckTray);
		m_nError = 0;
		return;
	}
	//��λ����ȡ������̶����Ƿ�ִ�����
	if (strRecevice.toUpper() == SuckTrayFail && m_Action == Action_SuckTray)
	{
		if (m_nError == ERRORNUM)
		{
			m_Action = Action_Null;
			emit sig_SuckTrayFinish();
			m_nError = 0;
			return;
		}
		gbl485SerialPort->AddTask(AskSuckTray);	
		m_nError = m_nError + 1;
		return;
	}
	//�����ס����
	if (strRecevice.toUpper() == SuckTraySucess && m_Action == Action_SuckTray)
	{
		m_Action = Action_Null;
		emit sig_SuckTrayFinish();
		return;
	}

	/*********�ſ�����*****************/
	//��λ���յ��ſ���������
	if (strRecevice.toUpper() == WantDropTray)
	{
		//��λ������ִ�е����ſ����̿�ʼ����
		m_Action = Action_DropTray;
		gbl485SerialPort->AddTask(StartDropTray);
		return;
	}
	if (strRecevice.toUpper() == StartDropTray && m_Action == Action_DropTray)
	{
		//��λ����ȡ��ŷ��̶����Ƿ�ִ����ɣ�
		gbl485SerialPort->AddTask(AskDropTray );
		m_nError = 0;
		return;
	}
	//��λ����ȡ��ŷſ��̶����Ƿ�ִ�����
	if (strRecevice.toUpper() == DropTrayFail && m_Action == Action_DropTray)
	{
		if (m_nError == ERRORNUM)
		{
			m_Action = Action_Null;
			emit sig_DropTrayFinish();
			m_nError = 0;
			return;

		}
		gbl485SerialPort->AddTask(AskDropTray);
		m_nError = m_nError + 1;
		return;
	}
	//��ɷ�������
	if (strRecevice.toUpper() == DropTraySucess && m_Action == Action_DropTray)
	{
		m_Action = Action_Null;
		emit sig_DropTrayFinish();
		return;
	}

	/**********��ȡ����*****************/
	//PLC���յ���λ����������
	if (strRecevice.toUpper() == WantGetGoods)
	{
		//��λ�����Ϳ�ʼִ����ȡ��������
		m_Action = Action_GetGoods;
		gbl485SerialPort->AddTask(StartGetGoods);
		return;
	}
	if (strRecevice.toUpper() == StartGetGoods && m_Action == Action_GetGoods)
	{
		//��λ����ȡ������̶����Ƿ�ִ����ɣ�
		gbl485SerialPort->AddTask(AskGetGoods);
		Sleep(10);
		GetHeight();
		return;
	}
	//��λ����ȡ������̶����Ƿ�ִ�����
	if (strRecevice.toUpper() == GetGoodsFail && m_Action == Action_GetGoods)
	{
		gbl485SerialPort->AddTask(AskGetGoods);
		Sleep(10);
		GetHeight();
		return;
	}
	//�����ȡ��������
	if (strRecevice.toUpper() == GetGoodsSucess && m_Action == Action_GetGoods)
	{
		m_Action = Action_Null;
		emit sig_GetGoodsFinish();
		return;
	}

	/**********���͵�λ*****************/
	//PLC���յ���λ�����ͻ�������
	if (strRecevice.toUpper() == WantPushGoods)
	{
		//�յ���ִ�����ͻ���
		m_Action = Action_PushGoods;
		gbl485SerialPort->AddTask(StartPushGoods);
		return;
	}
	if (strRecevice.toUpper() == StartPushGoods && m_Action == Action_PushGoods)
	{
		//���͵�λû�У���
		gbl485SerialPort->AddTask(AskPushGoods);
		return;
	}
	//���͵�λû�У�
	if (strRecevice.toUpper() == PushGoodsFail && m_Action == Action_PushGoods)
	{
		gbl485SerialPort->AddTask(AskPushGoods);
		return;
	}
	//�Ѿ����͵�λ
	if (strRecevice.toUpper() == PushGoodsSucess && m_Action == Action_PushGoods)
	{
		m_Action = Action_Null;
		emit sig_PushGoodsFinish();
		return;
	}

	/********�˶�������******************/
	//PLC�յ�������Ϣ
	if (strRecevice.toUpper() == m_strMoveToX)
	{
		//����������Ϣ
		m_Action = Action_Move;
		gbl485SerialPort->AddTask(m_strMoveToY);
		return;
	}
	//PLC�յ�������Ϣ
	if (strRecevice.toUpper() == m_strMoveToY && m_Action == Action_Move)
	{
		//��ʼ�˶�����Ӧ���С���
		gbl485SerialPort->AddTask(StartMove);
		return;
	}
	//PLC�յ�������Ϣ
	if (strRecevice.toUpper() == StartMove && m_Action == Action_Move)
	{
		//��ʼ�˶�����Ӧ���С���
		gbl485SerialPort->AddTask(AskMove);
		return;
	}

	//��λ��ѯ���Ƿ�ﵽ��Ӧ���С���λ�ã�
	if (strRecevice.toUpper() == MoveFail && m_Action == Action_Move)
	{
		gbl485SerialPort->AddTask(AskMove);
		return;
	}
	//�Ѵﵽָ���С���λ��
	if (strRecevice.toUpper() == MoveSucess && m_Action == Action_Move)
	{
		m_Action = Action_Null;
		emit sig_MoveFinish();
		return;
	}

	if (strRecevice.indexOf("3A 30 32 30 33 30 32") != -1)
	{
		emit sig_ReadSetting(m_Action, strRecevice);
		return;
	}
}

bool QPortControl::OpenDoor()
{
	restart();
	gbl485SerialPort->AddTask(WantOpenDoor);
	return true;

}

bool QPortControl::CloseDoor() 
{
	restart();
	gbl485SerialPort->AddTask(WantDoorClose);
	return true;
}
//��ס����
bool QPortControl::SuckTray()
{
	restart();
	gbl485SerialPort->AddTask(WantSuckTray);
	return true;
}

//��ס����
bool QPortControl::DropTray()
{
	restart();
	gbl485SerialPort->AddTask(WantDropTray);
	return true;
}

//��ȡ����
void QPortControl::GetGoods()
{//��λ��������ȡ��������
	restart();
	gbl485SerialPort->AddTask(WantGetGoods);
}

int Hextoi(QString s, char len)
{
	int i;
	int n = 0;

	if (s.length() < len) return 0; //������٣�ָ���������  

	for (i = 0; i < len; ++i)
	{
		if (s.at(i) > '9')
		{
			n = 16 * n + (10 + s.at(i).toLatin1() - 'A');
		}
		else
		{
			n = 16 * n + (s.at(i).toLatin1() - '0');
		}
	}
	return n;
}

QString hextoAss(QString i)
{
	if (i == ' ')
		return "";
	if (i < '9' || i == '9')
	{
		i = "3" + i;
	}
	else
	{
		if (i=='A')
		{
			i = "41";
		}
		if (i == 'B')
		{
			i = "42";
		}
		if (i == 'C')
		{
			i = "43";
		}
		if (i == 'D')
		{
			i = "44";
		}
		if (i == 'E')
		{
			i = "45";
		}
		if (i == 'F')
		{
			i = "46";
		}
	}
	i =   i+ ' ';
	return i;
}

QString PointToHex(int nRow,QString strSend)
{
	QString strRow = QString("%1").arg(nRow, 2, 16, QLatin1Char('0'));

	strSend = strSend +" "+ strRow.toUpper();
	QStringList lst;
	lst = strSend.split(' ');
	int num = 0;
	bool ok;
	unsigned char sum;
	for (int i = 0; i < lst.size(); i++)
	{
		QString str1 = lst[i];
		num += Hextoi(str1, 2);
	}
	num = ~num;
	num += 1;
	strRow = QString("%1").arg(num, 2, 16, QLatin1Char('0'));

	strSend = strSend+ " "+strRow.right(2).toUpper() ;
	QString strNew="3A ";
	for (int i = 0; i < strSend.length(); i++)
	{
		strNew += hextoAss(strSend.at(i));
	}
	strNew = strNew + MOVEEND;
	return strNew;
}

void  QPortControl::MovePoint(int nRow, int nColumn)
{
	m_nRow = nRow;
	m_nColumn = nColumn;

	if (nRow == 0 && nColumn == 0)
	{
		m_strMoveToX = MOVEZEROROW;
		m_strMoveToY = MOVEZEROCOLUMN;
	}
	else
	{
		m_strMoveToX = PointToHex(nRow, CountX);
		m_strMoveToY = PointToHex(nColumn, CountY);
	}
	
	restart();
	gbl485SerialPort->AddTask(m_strMoveToX);
}

void QPortControl::restart()
{
	gbl485SerialPort->close();
	gbl485SerialPort->InitSerial();

}

void QPortControl::PushGoods()
{
	restart();
	gbl485SerialPort->AddTask(WantPushGoods);
	return;
}

void QPortControl::SetZero()
{
	gbl232SerialPort->AddTask(SETWEIGHTZERO);
	return;
}

void QPortControl::slot_232ReadData(QString strRecevice)
{
	strRecevice.replace(" 02 40 6", "02 40 6");
	LOG_INFO("strRecevice=[%s]", strRecevice.toStdString().c_str());

	if (strRecevice.toUpper() == ZEROWEIGHT)
	{
		gblRuntimeData->strWeight = "0";
		return;
	}
	if (strRecevice.toUpper().indexOf("02 40 62")!= -1)
	{
		QString strweight;
		int strten;
		if (strRecevice.section(" ", 5, 5).toInt() < 30)
		{
			strten = 0;
		}
		else
		{
			strten = strRecevice.section(" ", 5, 5).toInt() - 30;
		}
		if (strten > 2)
		{	
			emit sig_overWeight();
			gblRuntimeData->strWeight = "����";
			return;		
		}
		int strone = strRecevice.section(" ", 6, 6).toInt() - 30;
		QString strpoint = ".";
		int strpointone = strRecevice.section(" ", 8, 8).toInt() - 30;
		int strpointten = strRecevice.section(" ", 9, 9).toInt() - 30;
		double weight = strten * 10 + strone + strpointone * 0.1 + strpointten * 0.01;
		/*	if (weight - gblRuntimeData->strWeight.toDouble() > 0)
			{

			}*/
		if (weight-1.86>0)
		{
			gblRuntimeData->strWeight = QString::number((weight-1.86), 10, 2);
		}
		else
		{
			gblRuntimeData->strWeight = QString::number(weight, 10, 2);
		}
		
		LOG_INFO("weight =[%f], strWeight=[%s]", weight, gblRuntimeData->strWeight.toStdString().c_str());
	}
}

void QPortControl::slot_heightReadData(QString strRecevice)
{
	LOG_INFO("heightReadData=[%s]", strRecevice.toStdString().c_str());

	if (strRecevice.toUpper().indexOf("01 03 04") != -1)
	{
		int height2 = strRecevice.section(" ", 6, 6).toInt(0, 16)*20+40;
		if (height2 == 40)
		{
			height2 = 30;
		}
		if (height2 - gblRuntimeData->strHeight.toInt()>0)
		{
			gblRuntimeData->strHeight = QString::number(height2);
		}
		
	}

}

void QPortControl::setReadState(bool bRead)
{
	gbl232SerialPort->setReadState(bRead);
	//gblRuntimeData->strWeight="0";
}

void QPortControl::GetHeight()
{
	gbl485HeightPort->AddTask(GEIHEIGHT);


}

QString ValueToHex(QString strSend,int nValue)
{
	QString strValue = QString("%1").arg(nValue, 4, 16, QLatin1Char('0'));
	strSend = strSend + " " + strValue.mid(0,2).toUpper() + " " + strValue.mid(2, 2).toUpper();
	QStringList lst;
	lst = strSend.split(' ');
	int num = 0;
	bool ok;
	unsigned char sum;
	for (int i = 0; i < lst.size(); i++)
	{
		QString str1 = lst[i];
		num += Hextoi(str1, 2);
	}
	num = ~num;
	num += 1;
	QString	strLRC = QString("%1").arg(num, 2, 16, QLatin1Char('0'));
	strSend = strSend + " " + strLRC.right(2).toUpper();
	
	QString strNew = "3A ";
	for (int i = 0; i < strSend.length(); i++)
	{
		strNew += hextoAss(strSend.at(i));
	}
	strNew = strNew + MOVEEND;
	
	return strNew;
}


void QPortControl::move_setting(int nValue)
{
	QString strSend = "02 06 17 D0";
	strSend = ValueToHex(strSend, nValue);
	gbl485SerialPort->AddTask(strSend);

}

void QPortControl::move_read()
{
	gbl485SerialPort->AddTask("3A 30 32 30 33 31 37 44 30 30 30 30 31 31 33 0D 0A");
	m_Action = Action_Read_Move;
}

void QPortControl::rotate_setting(int nValue)
{
	QString strSend = "02 06 17 DA";
	strSend = ValueToHex(strSend, nValue);


	gbl485SerialPort->AddTask(strSend);

}

void QPortControl::rotate_read()
{
	gbl485SerialPort->AddTask("3A 30 32 30 33 31 37 44 41 30 30 30 31 30 39 0D 0A");
	m_Action = Action_Read_Rotate;
}

void QPortControl::tray_setting(int nValue)
{

	QString strSend = "02 06 17 E4";
	strSend = ValueToHex(strSend, nValue);
	gbl485SerialPort->AddTask(strSend);

}

void QPortControl::tray_read()
{
	gbl485SerialPort->AddTask("3A 30 32 30 33 31 37 45 34 30 30 30 31 46 46 0D 0A");
	m_Action = Action_Read_Tray;
}

void QPortControl::door_setting(int nValue)
{
	QString strSend = "02 06 17 EE";
	strSend = ValueToHex(strSend, nValue);
	gbl485SerialPort->AddTask(strSend);
}

void QPortControl::door_read()
{
	gbl485SerialPort->AddTask("3A 30 32 30 33 31 37 45 45 30 30 30 31 46 35 0D 0A");
	m_Action = Action_Read_Door;
}

void QPortControl::zero_setting(int nValue)
{

	QString strSend = "02 06 1F A0";
	strSend = ValueToHex(strSend, nValue);
	gbl485SerialPort->AddTask(strSend);

}

void QPortControl::zero_read()
{
	gbl485SerialPort->AddTask("3A 30 32 30 33 31 46 41 30 30 30 30 31 33 42 0D 0A");
	m_Action = Action_Read_Zero;
}

