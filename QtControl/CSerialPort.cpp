#include "CSerialPort.h"

#include "Base/myhelper.h"
#include "Base/RunTime.h"


CSerialPort::CSerialPort(QObject *parent)
	: QObject(parent)
{
}

CSerialPort::~CSerialPort()
{
}

CSerialPort_232::CSerialPort_232(QObject *parent)
	: QObject(parent)
{
	gblRuntimeData->ReadConfig();
	InitSerial();
}

CSerialPort_232::~CSerialPort_232()
{
	if (com != 0 && com->isOpen())
	{
		com->close();
		return;
	}
}

void CSerialPort_232::InitSerial()
{
	//���ô�����  
	m_serial = new QSerialPort;
	//���ô�����  
	m_serial->setPortName(gblRuntimeData->com232_PortName);
	//�򿪴���  
	bool bOpen = m_serial->open(QIODevice::ReadWrite);
	if (!bOpen)
	{
		return;
	}
	//���ò�����  
	m_serial->setBaudRate(gblRuntimeData->com232_BaudRate);
	//��������λ��  
	switch (gblRuntimeData->com232_DataBit)
	{
	case 5:
		m_serial->setDataBits(QSerialPort::Data5);
		break;
	case 6:
		m_serial->setDataBits(QSerialPort::Data6);
		break;
	case 7:
		m_serial->setDataBits(QSerialPort::Data7);
		break;
	case 8:
		m_serial->setDataBits(QSerialPort::Data8);
		break;
	default:
		m_serial->setDataBits(QSerialPort::UnknownDataBits);
		break;
	}
	//������żУ��  
	if (gblRuntimeData->com232_Parity == "��" )
	{
		m_serial->setParity(QSerialPort::NoParity);
	}
	if (gblRuntimeData->com232_Parity == "��")
	{
		m_serial->setParity(QSerialPort::OddParity);
	}
	if (gblRuntimeData->com232_Parity == "ż")
	{
		m_serial->setParity(QSerialPort::EvenParity);
	}
	if (gblRuntimeData->com232_Parity == "��־")
	{
		m_serial->setParity(QSerialPort::MarkParity);
	}
	if (gblRuntimeData->com232_Parity == "�ո�")
	{
		m_serial->setParity(QSerialPort::SpaceParity);
	}

	//����ֹͣλ  
	if (gblRuntimeData->com232_StopBit == 1)
	{
	    m_serial->setStopBits(QSerialPort::OneStop); 
	}
	else if (gblRuntimeData->com232_StopBit == 1.5)
	{
		m_serial->setStopBits(QSerialPort::OneAndHalfStop);
	}
	else if (gblRuntimeData->com232_StopBit == 2)
	{
		m_serial->setStopBits(QSerialPort::TwoStop);
	}
	//����������  
	m_serial->setFlowControl(QSerialPort::NoFlowControl);
	//�����źŲ�  
	QObject::connect(m_serial, &QSerialPort::readyRead, this, &CSerialPort_232::readData);
}


void CSerialPort_232::InitQextSerial()
{
	com = new QextSerialPort(gblRuntimeData->com232_PortName, QextSerialPort::EventDriven);
	comOk = com->open(QIODevice::ReadWrite);
	if (comOk)
	{
		//��ջ�����
		com->flush();
		//���ò�����
		com->setBaudRate((BaudRateType)gblRuntimeData->com232_BaudRate);
	
		//��������λ
		switch (gblRuntimeData->com232_DataBit)
		{
		case 5:
			com->setDataBits((DataBitsType)DATA_5);
			break;
		case 6:
			com->setDataBits((DataBitsType)DATA_6);
			break;
		case 7:
			com->setDataBits((DataBitsType)DATA_7);	
			break;
		case 8:
			com->setDataBits((DataBitsType)DATA_8);	
			break;

		}
		//������żУ��  
		if (gblRuntimeData->com232_Parity == "��")
		{
			com->setParity((ParityType)PAR_NONE);
		}
		if (gblRuntimeData->com232_Parity == "��")
		{
			com->setParity((ParityType)PAR_ODD);

		}
		if (gblRuntimeData->com232_Parity == "ż")
		{
			com->setParity((ParityType)PAR_EVEN);
			
		}
		if (gblRuntimeData->com232_Parity == "��־")
		{
			com->setParity((ParityType)PAR_MARK);
		
		}
		if (gblRuntimeData->com232_Parity == "�ո�")
		{
			com->setParity((ParityType)PAR_SPACE);
		
		}
		//����ֹͣλ  
		if (gblRuntimeData->com232_StopBit == 1)
		{
			com->setStopBits((StopBitsType)STOP_1);		
		}
		else if (gblRuntimeData->com232_StopBit == 1.5)
		{
			com->setStopBits((StopBitsType)STOP_1_5);		
		}
		else if (gblRuntimeData->com232_StopBit == 2)
		{
			com->setStopBits((StopBitsType)STOP_2);
		
		}		
		com->setFlowControl(FLOW_OFF);
		com->setTimeout(10);
		connect(com, SIGNAL(readyRead()), this, SLOT(QextreadData()));

	}
}

void CSerialPort_232::readData()
{
	QByteArray data;
	QString buffer;
	data = m_serial->readAll();
	if (gblRuntimeData->com232_HexReceive)
	{
		buffer = myHelper::byteArrayToHexStr(data);
	}
	else
	{
		buffer = myHelper::byteArrayToAsciiStr(data);
	}
	if (buffer.isEmpty() == true)
	{
		return;
	}
	emit sig_ReadData(buffer);
	buffer.clear();
}

void CSerialPort_232::QextreadData()
{

	QString buffer;
	QByteArray data = com->readAll();

	if (gblRuntimeData->com232_HexReceive)
	{
		buffer = myHelper::byteArrayToHexStr(data);
	}
	else
	{
		buffer = myHelper::byteArrayToAsciiStr(data);
	}
	if (buffer.isEmpty() == true)
	{
		return;
	}
	emit sig_ReadData(buffer);
	buffer.clear();

}

void CSerialPort_232::sendData(QString data)
{
	if (m_serial->isOpen() != true)
	{
		return;
	}

	QByteArray buffer;

	if (gblRuntimeData->com232_HexSend)
	{
		buffer = myHelper::hexStrToByteArray(data);
	}
	else
	{
		buffer = myHelper::asciiStrToByteArray(data);
	}

	m_serial->write(buffer);
}

void CSerialPort_232::QextsendData(QString data)    //���ʹ������ݴ�����
{
	if (com == 0 || !com->isOpen()) {
		return;
	}

	QByteArray buffer;

	if (gblRuntimeData->com232_HexSend)
	{
		buffer = myHelper::hexStrToByteArray(data);
	}
	else
	{
		buffer = myHelper::asciiStrToByteArray(data);
	}
	


	com->write(buffer);


}





CSerialPort_485::CSerialPort_485(QObject *parent)
	: QObject(parent)
{
	gblRuntimeData->ReadConfig();
	InitSerial();
}

CSerialPort_485::~CSerialPort_485()
{
}

void CSerialPort_485::InitSerial()
{
	//���ô�����  
	m_serial = new QSerialPort;
	//���ô�����  
	m_serial->setPortName(gblRuntimeData->com485_PortName);
	//�򿪴���  
	bool bOpen = m_serial->open(QIODevice::ReadWrite);
	if (!bOpen)
	{
		return;
	}
	//���ò�����  
	m_serial->setBaudRate(gblRuntimeData->com485_BaudRate);
	//��������λ��  
	switch (gblRuntimeData->com485_DataBit)
	{
	case 5:
		m_serial->setDataBits(QSerialPort::Data5);
		break;
	case 6:
		m_serial->setDataBits(QSerialPort::Data6);
		break;
	case 7:
		m_serial->setDataBits(QSerialPort::Data7);
		break;
	case 8:
		m_serial->setDataBits(QSerialPort::Data8);
		break;
	default:
		m_serial->setDataBits(QSerialPort::UnknownDataBits);
		break;
	}
	//������żУ��  
	if (gblRuntimeData->com485_Parity == "��")
	{
		m_serial->setParity(QSerialPort::NoParity);
	}
	if (gblRuntimeData->com485_Parity == "��")
	{
		m_serial->setParity(QSerialPort::OddParity);
	}
	if (gblRuntimeData->com485_Parity == "ż")
	{
		m_serial->setParity(QSerialPort::EvenParity);
	}
	if (gblRuntimeData->com485_Parity == "��־")
	{
		m_serial->setParity(QSerialPort::MarkParity);
	}
	if (gblRuntimeData->com485_Parity == "�ո�")
	{
		m_serial->setParity(QSerialPort::SpaceParity);
	}

	//����ֹͣλ  
	if (gblRuntimeData->com485_StopBit == 1)
	{
		m_serial->setStopBits(QSerialPort::OneStop);
	}
	else if (gblRuntimeData->com485_StopBit == 1.5)
	{
		m_serial->setStopBits(QSerialPort::OneAndHalfStop);
	}
	else if (gblRuntimeData->com485_StopBit == 2)
	{
		m_serial->setStopBits(QSerialPort::TwoStop);
	}
	//����������  
	m_serial->setFlowControl(QSerialPort::NoFlowControl);
	//�����źŲ�  
	QObject::connect(m_serial, &QSerialPort::readyRead, this, &CSerialPort_485::readData);
}


void CSerialPort_485::readData()
{
	QByteArray data;
	QString buffer;
	data = m_serial->readAll();
	if (gblRuntimeData->com485_HexReceive)
	{
		buffer = myHelper::byteArrayToHexStr(data);
	}
	else
	{
		buffer = myHelper::byteArrayToAsciiStr(data);
	}
	if (buffer.isEmpty() == true)
	{
		return;
	}
	emit sig_ReadData(buffer);
	buffer.clear();
}



void CSerialPort_485::sendData(QString data)
{
	if (m_serial->isOpen() != true)
	{
		return;
	}

	QByteArray buffer;

	if (gblRuntimeData->com485_HexSend)
	{
		buffer = myHelper::hexStrToByteArray(data);
	}
	else
	{
		buffer = myHelper::asciiStrToByteArray(data);
	}

	m_serial->write(buffer);
}