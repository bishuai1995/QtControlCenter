#pragma once

#include <QWidget>
#include <QWidget>
#include <QSignalMapper>
#include <QMouseEvent>
#include "ui_NumKeyBoard.h"

class NumKeyBoard : public QWidget,public Ui::NumKeyBoard
{
	Q_OBJECT

public:
	NumKeyBoard(QWidget *parent = Q_NULLPTR);
	~NumKeyBoard();
private:

	void mouseMoveEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *);
	enum
	{
		iMode_Normal = 0,
		iMode_Passwd = 1
	}; //����ģʽ������ģʽ
private:
	void setMapper();
	void connectMapper();
	void button_init();

public:
	QString text;
signals:
	void setvalue(QString text);
private slots:
	void setDispText(const QString& text);
	void onEnter();
	void onBackspace();

	/*******��Сд*/
	void onInvMode();

	void  on_slot_textChanged(const QString &text);
private:
	int inputMode;
	bool waitingForOperand;
	QSignalMapper *signalMapper;
	QPoint dragPosition;
	bool caps_Lock;
};
