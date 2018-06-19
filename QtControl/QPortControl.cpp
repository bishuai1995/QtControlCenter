#include "QPortControl.h"
#include <QMessageBox>
QPortControl::QPortControl(QObject *parent)
	: QObject(parent)
{
	


	connect(gbl485SerialPort, SIGNAL(sig_ReadData(QString)), this, SLOT(slot_ReadData(QString)));

}

QPortControl::~QPortControl()
{
}

void QPortControl::slot_ReadData(QString strRecevice)
{
	//��λ���յ���������
	if (strRecevice.toUpper() == WantOpenDoor)
	{
		//��λ�����Ϳ�ʼִ�п��Ŷ���
		m_Action = Action_OpenDoor;
		gbl485SerialPort->sendData(StartOpenDoor);
		return;
	}
	//��λ�����Ϳ�ʼִ�п��Ŷ���
	if (strRecevice.toUpper() == StartOpenDoor && m_Action == Action_OpenDoor)
	{		
		gbl485SerialPort->sendData(AskOpenDoor);
		return;
	}
	//��λ�����Ϳ�ʼִ�п��Ŷ���
	if (strRecevice.toUpper() == OpenDoorFail && m_Action == Action_OpenDoor)
	{
		gbl485SerialPort->sendData(AskOpenDoor);
		return;
	}
	//��λ���յ����ųɹ����ź�
	if (strRecevice.toUpper() == OpenDoorSucess&& m_Action == Action_OpenDoor)
	{
		emit sig_OpendoorFinish();
		return;
	}

	/**********����*****************/
	//��λ���յ���������
	if (strRecevice.toUpper() == WantDoorClose)
	{
		//��λ�����Ϳ�ʼִ�й��Ŷ���
		m_Action = Action_CloseDoor;
		gbl485SerialPort->sendData(StartCloseDoor);
		return;
	}
	//��λ��ѯ���Ƿ���ɹ����Ŷ�����
	if (strRecevice.toUpper() == StartCloseDoor && m_Action == Action_CloseDoor)
	{
		gbl485SerialPort->sendData(AskCloseDoor);
		return;
	}
	//��λ�����Ϳ�ʼִ�й��Ŷ���
	if (strRecevice.toUpper() == CloseDoorFail && m_Action == Action_CloseDoor)
	{
		gbl485SerialPort->sendData(AskCloseDoor);
		return;
	}
	//��λ���յ����ųɹ����ź�
	if (strRecevice.toUpper() == CloseDoorSucess && m_Action == Action_CloseDoor)
	{
		emit sig_ClosedoorFinish();
		return;
	}

	/**********��ס����*****************/
	//��λ���յ���ס��������
	if (strRecevice.toUpper() == WantSuckTray)
	{
		m_Action = Action_SuckTray;
		//��λ������ִ�е������ס���̿�ʼ����
		gbl485SerialPort->sendData(StartSuckTray);
		return;
	}	
	if (strRecevice.toUpper() == StartSuckTray && m_Action == Action_SuckTray)
	{
		//��λ����ȡ������̶����Ƿ�ִ����ɣ�
		gbl485SerialPort->sendData(AskSuckTray);
		return;
	}
	//��λ����ȡ������̶����Ƿ�ִ�����
	if (strRecevice.toUpper() == SuckTrayFail && m_Action == Action_SuckTray)
	{
		//gbl485SerialPort->sendData(AskSuckTray);
		emit sig_SuckTrayFinish();
		return;
	}
	//�����ס����
	if (strRecevice.toUpper() == SuckTraySucess && m_Action == Action_SuckTray)
	{
		emit sig_SuckTrayFinish();
		return;
	}

	/*********�ſ�����*****************/
	//��λ���յ��ſ���������
	if (strRecevice.toUpper() == WantDropTray)
	{
		//��λ������ִ�е����ſ����̿�ʼ����
		m_Action = Action_DropTray;
		gbl485SerialPort->sendData(StartDropTray);
		return;
	}
	if (strRecevice.toUpper() == StartDropTray && m_Action == Action_DropTray)
	{
		//��λ����ȡ��ŷ��̶����Ƿ�ִ����ɣ�
		gbl485SerialPort->sendData(AskDropTray );
		return;
	}
	//��λ����ȡ��ŷſ��̶����Ƿ�ִ�����
	if (strRecevice.toUpper() == DropTrayFail && m_Action == Action_DropTray)
	{
		//gbl485SerialPort->sendData(AskDropTray);
		emit sig_DropTrayFinish();
		return;
	}
	//��ɷ�������
	if (strRecevice.toUpper() == DropTraySucess && m_Action == Action_DropTray)
	{
		emit sig_DropTrayFinish();
		return;
	}

	/**********��ȡ����*****************/
	//PLC���յ���λ����������
	if (strRecevice.toUpper() == WantGetGoods)
	{
		//��λ�����Ϳ�ʼִ����ȡ��������
		m_Action = Action_GetGoods;
		gbl485SerialPort->sendData(StartGetGoods);
	}
	if (strRecevice.toUpper() == StartGetGoods && m_Action == Action_GetGoods)
	{
		//��λ����ȡ������̶����Ƿ�ִ����ɣ�
		gbl485SerialPort->sendData(AskGetGoods);
	}
	//��λ����ȡ������̶����Ƿ�ִ�����
	if (strRecevice.toUpper() == GetGoodsFail && m_Action == Action_GetGoods)
	{
		gbl485SerialPort->sendData(AskGetGoods);
	}
	//�����ȡ��������
	if (strRecevice.toUpper() == GetGoodsSucess && m_Action == Action_GetGoods)
	{
		emit sig_GetGoodsFinish();
	}


	/**********���͵�λ*****************/
	//PLC���յ���λ�����ͻ�������
	if (strRecevice.toUpper() == WantPushGoods)
	{
		//�յ���ִ�����ͻ���
		m_Action = Action_PushGoods;
		gbl485SerialPort->sendData(StartPushGoods);
	}
	if (strRecevice.toUpper() == StartPushGoods && m_Action == Action_PushGoods)
	{
		//���͵�λû�У���
		gbl485SerialPort->sendData(AskPushGoods);
	}
	//���͵�λû�У�
	if (strRecevice.toUpper() == PushGoodsFail && m_Action == Action_PushGoods)
	{
		gbl485SerialPort->sendData(AskPushGoods);
	}
	//�Ѿ����͵�λ
	if (strRecevice.toUpper() == PushGoodsSucess && m_Action == Action_PushGoods)
	{
		emit sig_PushGoodsFinish();
	}

	/********�˶�������******************/
	//PLC�յ�������Ϣ
	if (strRecevice.toUpper() == m_strMoveToX)
	{
		//����������Ϣ
		m_Action = Action_Move;
		gbl485SerialPort->sendData(m_strMoveToY);
	}
	//PLC�յ�������Ϣ
	if (strRecevice.toUpper() == m_strMoveToY && m_Action == Action_Move)
	{
		//��ʼ�˶�����Ӧ���С���
		gbl485SerialPort->sendData(StartMove);
	}
	//PLC�յ�������Ϣ
	if (strRecevice.toUpper() == StartMove && m_Action == Action_Move)
	{
		//��ʼ�˶�����Ӧ���С���
		gbl485SerialPort->sendData(AskMove);
	}

	//��λ��ѯ���Ƿ�ﵽ��Ӧ���С���λ�ã�
	if (strRecevice.toUpper() == MoveFail && m_Action == Action_Move)
	{
		gbl485SerialPort->sendData(AskMove);
	}
	//�Ѵﵽָ���С���λ��
	if (strRecevice.toUpper() == MoveSucess && m_Action == Action_Move)
	{
		emit sig_MoveFinish();
	}

}


bool QPortControl::OpenDoor()
{
	gbl485SerialPort->close();
	gbl485SerialPort->InitSerial();

	gbl485SerialPort->sendData(WantOpenDoor);
	return true;

}

bool QPortControl::CloseDoor() 
{
	gbl485SerialPort->close();
	gbl485SerialPort->InitSerial();
	gbl485SerialPort->sendData(WantDoorClose);
	return true;
}
//��ס����
bool QPortControl::SuckTray()
{
	gblRuntimeData->Recevice_485.clear();
	gbl485SerialPort->sendData(WantSuckTray);
	return true;
}

//��ס����
bool QPortControl::DropTray()
{
	gblRuntimeData->Recevice_485.clear();
	gbl485SerialPort->sendData(WantDropTray);
	return true;
}

//��ȡ����
void QPortControl::GetGoods()
{//��λ��������ȡ��������
	gbl485SerialPort->sendData(WantGetGoods);
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
	
	gbl485SerialPort->sendData(m_strMoveToX);
}

void QPortControl::restart()
{
	gbl485SerialPort->close();
	gbl485SerialPort->InitSerial();
}

void QPortControl::PushGoods()
{
	gbl485SerialPort->sendData(WantPushGoods);
	return;
}