#pragma once

#include <QDialog>
#include <QMovie> 
#include "ui_CQRWidget.h"
#include "define.h"
class CQRWidget : public QDialog,public Ui::CQRWidget
{
	Q_OBJECT

public:
	CQRWidget(QWidget *parent = Q_NULLPTR);
	~CQRWidget();

	/*
	* DateTime : 2017-08-09
	* Describe : ��ʼ�� ����Ϣ���ѿ�ֵ״̬
	*/
	void Init(WIDGET_TYPE types);


private slots:
	void on_btnBack_clicked();

	void on_btnHome_clicked();

	void on_slot_timeout();

private:
	QMovie * pMove;
};
