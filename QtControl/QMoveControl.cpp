#include "QMoveControl.h"
#include <QMessageBox>
QMoveControl::QMoveControl(QObject *parent)
	: QObject(parent)
{
	m_bSecond = false;

	connect(gblPortControl, SIGNAL(sig_MoveFinish()), this, SLOT(on_slot_MoveFinish()));

	connect(gblPortControl, SIGNAL(sig_PushGoodsFinish()), this, SLOT(on_slot_PushGoodsFinish()));

	connect(gblPortControl, SIGNAL(sig_GetGoodsFinish()), this, SLOT(on_slot_GetGoodsFinish()));

	connect(gblPortControl, SIGNAL(sig_SuckTrayFinish()), this, SLOT(on_slot_SuckTrayFinish()));

	connect(gblPortControl, SIGNAL(sig_DropTrayFinish()), this, SLOT(on_slot_DropTrayFinish()));
	
}

QMoveControl::~QMoveControl()
{
}

void QMoveControl::SetMove(QPoint startPoint, QPoint endPoint)
{
	m_StartPoint = startPoint;
	m_EndPoint = endPoint;
}
void QMoveControl::StartWork()
{	
	gblPortControl->restart();

	//1.������
	gblPortControl->GetGoods();   
	m_bSecond = false;
	m_bFinish = false;
}


void QMoveControl::on_slot_MoveFinish()
{
	if (m_bFinish==true)
	{
		return;
	}
	if (m_bSecond == false)
	{
		//3.�Ƴ�ȥ
		gblPortControl->PushGoods();
	}
	else
	{
		//7.�Ƴ�ȥ
		gblPortControl->PushGoods();
	}
}

void QMoveControl::on_slot_PushGoodsFinish()
{
	if (m_bFinish == true)
	{
		return;
	}
	if (m_bSecond == false)
	{
		//4.��ס
		gblPortControl->SuckTray();
	}
	else
	{
		//8.�ſ�����
		gblPortControl->DropTray();
	}
}

void QMoveControl::on_slot_GetGoodsFinish()
{
	if (m_bFinish == true)
	{
		return;
	}
	if (m_bSecond == false)
	{
		//2.�ƶ�����ʼ��
		gblPortControl->MovePoint(m_StartPoint.x(), m_StartPoint.y());
	}
	else
	{
		//6.�ƶ�������λ��
		gblPortControl->MovePoint(m_EndPoint.x(), m_EndPoint.y());
	}


}

void QMoveControl::on_slot_SuckTrayFinish()
{
	if (m_bFinish == true)
	{
		return;
	}
	if (m_bSecond == false)
	{
		//5.������
		gblPortControl->GetGoods();
		m_bSecond = true;
	}
}

void QMoveControl::on_slot_DropTrayFinish()
{
	if (m_bFinish == true)
	{
		return;
	}

	if (m_bSecond == false)
	{
	}
	else
	{
		//9.��ɣ�
		emit sig_finish();	
		m_bFinish = true;
	}

}