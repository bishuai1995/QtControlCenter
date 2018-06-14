#pragma once
#pragma execution_character_set("utf-8")
#include <QObject>
#include <QSerialPort>  
#include <QSerialPortInfo>  
#include "define.h"
#include "include/HSingleton/HSingleton.h"
class CSerialPort : public QObject
{
	Q_OBJECT

public:
	CSerialPort(QObject *parent);


	~CSerialPort();
};


class CSerialPort_232 : public QObject
{
	Q_OBJECT

public:
	CSerialPort_232(QObject *parent);


	~CSerialPort_232();


	void InitSerial();			//��ʼ����������
	void InitQextSerial();			//��ʼ����������
signals: 
	void sig_ReadData(QString strData);

private slots:
	void readData();                //��ȡ��������

	void QextreadData();                //��ȡ��������

	void sendData(QString data);    //���ʹ������ݴ�����

	void QextsendData(QString data);    //���ʹ������ݴ�����
private:

	QextSerialPort * com;        //����ͨ�Ŷ���

	QSerialPort * m_serial;

	bool comOk;                 //�����Ƿ��
};


#define gbl232SerialPort HSingletonTemplatePtr<CSerialPort_232>::get() ;




class CSerialPort_485 : public QObject
{
	Q_OBJECT

public:
	CSerialPort_485(QObject *parent);


	~CSerialPort_485();


	void InitSerial();			//��ʼ����������

signals:
	void sig_ReadData(QString strData);

private slots:
	void readData();                //��ȡ��������
	void sendData(QString data);    //���ʹ������ݴ�����
private:
	QSerialPort * m_serial;
};


#define gbl232SerialPort HSingletonTemplatePtr<CSerialPort_485>::get();