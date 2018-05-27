#include "QtControl.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QSerialPort>
#include <QAction>
#include "define.h"
QtControl::QtControl(QWidget *parent)
	: QWidget(parent)
{

	this->setupUi(this);

//	initPort();
	parentWidget = parent;
	//InitkeyBoardDlg();
	show();
	//disPlayKeyBoard();

	connect(btn_get, SIGNAL(clicked()), this, SLOT(on_slot_Get()));
	connect(btn_setting, SIGNAL(clicked()), this, SLOT(on_slot_setting()));

	QPixmap midPix;
	QPixmap qrPixmap = myHelper::MakeQRPixmap("test", midPix, 100);

	label_QRImage->setPixmap(qrPixmap);

}
/****************************���ڳ�ʼ��*****************************/
void QtControl::initPort()
{
	//LOG_WARN("initPort","");
	//��ȡ������Ϣ
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		qDebug() << "Name:" << info.portName();
		qDebug() << "Description:" << info.description();
		qDebug() << "Manufacturer:" << info.manufacturer();

		//�����൱���Զ�ʶ�𴮿ں�֮����ӵ���cmb�����Ҫ�ֶ�ѡ������������б�ķ�ʽ��ӽ�ȥ
		QSerialPort serial;
		serial.setPort(info);
		if (serial.open(QIODevice::ReadWrite))
		{
			//�����ں���ӵ�cmb
			//ui->cmbPortName->addItem(info.portName());

			//�رմ��ڵȴ���Ϊ(�򿪴��ڰ�ť)��
			serial.close();
		}
	}

	QStringList baudList;//������
	QStringList parityList;//У��λ
	QStringList dataBitsList;//����λ
	QStringList stopBitsList;//ֹͣλ

	baudList << "50" << "75" << "100" << "134" << "150" << "200" << "300"
		<< "600" << "1200" << "1800" << "2400" << "4800" << "9600"
		<< "14400" << "19200" << "38400" << "56000" << "57600"
		<< "76800" << "115200" << "128000" << "256000";

	//ui->cmbBaudRate->addItems(baudList);
	//ui->cmbBaudRate->setCurrentIndex(12);

	parityList << "��" << "��" << "ż";
	parityList << "��־";
	parityList << "�ո�";

	//ui->cmbParity->addItems(parityList);
	//ui->cmbParity->setCurrentIndex(0);

	//dataBitsList << "5" << "6" << "7" << "8";
	//ui->cmbDataBits->addItems(dataBitsList);
	//ui->cmbDataBits->setCurrentIndex(3);

	stopBitsList << "1";
	stopBitsList << "1.5";
	stopBitsList << "2";

	//ui->cmbStopBits->addItems(stopBitsList);
//	ui->cmbStopBits->setCurrentIndex(0);

	//���ð�ť���Ա�����
	//ui->btnOpen->setCheckable(true);
}


void QtControl::InitkeyBoardDlg()
{
	keyBoardDlg = new KeyBoard();
	keyBoardDlg->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	connect(keyBoardDlg, SIGNAL(setvalue(QString)), this, SLOT(displayInputContent(QString)));
}

void QtControl::disPlayKeyBoard()
{
	keyBoardDlg->move(this->pos().x(), this->y() + this->frameGeometry().height());
	keyBoardDlg->show();

}
void QtControl::on_slot_Get()
{
	m_pNumKeyWidget.reset(new NumKeyBoard);
	m_pNumKeyWidget->showMaximized();
	this->hide();
}
void QtControl::on_slot_setting()
{
	m_pfrmWidget.reset(new frmComTool);
	m_pfrmWidget->showMaximized();
	this->hide();
}
void QtControl::displayInputContent(QString text)
{
	qDebug() << "TextEdit::displayInputContent";

}
