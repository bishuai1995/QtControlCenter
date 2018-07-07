#pragma once
#pragma execution_character_set("utf-8")
#include <QObject>
#include <QSerialPort>  
#include <QSerialPortInfo>  
#include "define.h"
#include <QThread>
#include <QWaitCondition>
#include "include/HSingleton/HSingleton.h"

class CSerialPort_232 : public QObject, public QThread
{
	Q_OBJECT
public:
	CSerialPort_232(QObject *parent = nullptr);

	~CSerialPort_232();
public:
	void InitSerial();			//��ʼ����������
	void close();
public:
	void AddTask(QString strSend);

	virtual  void run();

	void StopThread();
signals:
	void sig_ReadData(QString strData);

public slots:
	void readData();                //��ȡ��������

private slots:
	void sendData(QString data);    //���ʹ������ݴ�����
private:

	QextSerialPort * com;        //����ͨ�Ŷ���
	QTimer *timer;  //����������ʱ��  
	bool comOk;                 //�����Ƿ��
	QWaitCondition Thread_Wait;
private:
	QMutex m_QueyeMutex;
	QQueue<QString>	 m_szSendQueue;				//�ϴ�����
	volatile bool m_bAlive;
};


#define gbl232SerialPort HSingletonTemplatePtr<CSerialPort_232>::get() 




class CSerialPort_485 : public QObject, public QThread
{
	Q_OBJECT

public:
	CSerialPort_485(QObject *parent =nullptr);

	~CSerialPort_485();

	void InitSerial();			//��ʼ����������


	void close();

public:
	void AddTask(QString strSend);

	virtual  void run();

	void StopThread();
signals:
	void sig_ReadData(QString strData);

public slots:
	void readData();                //��ȡ��������

private slots:
	void sendData(QString data);    //���ʹ������ݴ�����
private:

	QextSerialPort *com;        //����ͨ�Ŷ���
	QTimer *timer;  //����������ʱ��  
	bool comOk;                 //�����Ƿ��
	QWaitCondition Thread_Wait;
private:
	QMutex m_QueyeMutex;
	QQueue<QString>	 m_szSendQueue;				//�ϴ�����
	volatile bool m_bAlive;

};


#define gbl485SerialPort HSingletonTemplatePtr<CSerialPort_485>::get()