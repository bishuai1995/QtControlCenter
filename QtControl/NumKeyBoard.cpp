#include "NumKeyBoard.h"

#include <QDebug>


NumKeyBoard::NumKeyBoard(QWidget *parent) :
	QDialog(parent)
{
	this->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint );
	this->setWindowIcon(QIcon(":/Image/Resources/Image/zhihuiwu.ico"));
	display->setFocus();
	//button_init();

	waitingForOperand = true;
	inputMode = iMode_Normal;
	caps_Lock = false;

	signalMapper = new QSignalMapper(this);
	setMapper();//������setMapper������Ӣ����ĸ���ּ��̼�Ⱥ�����źź���
	connectMapper();
	connect(signalMapper, SIGNAL(mapped(const QString&)),
		this, SLOT(setDispText(const QString&)));
	connect(toolButton_enter, SIGNAL(clicked()), this, SLOT(onEnter()));
	connect(toolButton_backspace, SIGNAL(clicked()), this, SLOT(onBackspace()));

	QRegExp regx("[0-9]+$");
	QValidator *validator = new QRegExpValidator(regx, display);
	display->setValidator(validator);
	display->hide();

	connect(display, &QLineEdit::textChanged,this, &NumKeyBoard::on_slot_textChanged);

	display->setMaxLength(6);

	connect(btn_back, SIGNAL(clicked()), this, SLOT(on_btnBack_clicked()));
	connect(btn_home, SIGNAL(clicked()), this, SLOT(on_btnHome_clicked()));

	connect(gblPortControl, SIGNAL(sig_OpendoorFinish()), this, SLOT(on_slot_OpendoorFinish()));

	connect(gblPortControl, SIGNAL(sig_MoveFinish()), this, SLOT(on_slot_MoveFinish()));

	connect(gblPortControl, SIGNAL(sig_PushGoodsFinish()), this, SLOT(on_slot_PushGoodsFinish()));

	connect(gblPortControl, SIGNAL(sig_SuckTrayFinish()), this, SLOT(on_slot_SuckTrayFinish()));
	
	connect(gblPortControl, SIGNAL(sig_GetGoodsFinish()), this, SLOT(on_slot_GetGoodsFinish()));
	
	connect(gblPortControl, SIGNAL(sig_DropTrayFinish()), this, SLOT(on_slot_DropTrayFinish()));

	connect(gblPortControl, SIGNAL(sig_ClosedoorFinish()), this, SLOT(on_slot_ClosedoorFinish()));


	display->setText("------");
	m_bSecond = false;
}

NumKeyBoard::~NumKeyBoard()
{
	
}
void NumKeyBoard::button_init()
{
	//����ɫֵ��#7a7675�� �ֺ�64px

	display->setStyleSheet("QLineEdit{font-size:25px;color:rgb(0,0,0);"
		"height:50px;border:2px solid rgb(4,167,240);"
		"border-radius:10px;}");
	toolButton_0->setStyleSheet("QToolButton{border:2px groove white;border-radius:10px;"
		"background-color:rgb(4,167,240);color:white;font-size:25px}");
	toolButton_1->setStyleSheet("QToolButton{border:2px groove white;border-radius:10px;"
		"background-color:rgb(4,167,240);color:white;font-size:25px}");
	toolButton_2->setStyleSheet("QToolButton{border:2px groove white;border-radius:10px;"
		"background-color:rgb(4,167,240);color:white;font-size:25px}");
	toolButton_3->setStyleSheet("QToolButton{border:2px groove white;border-radius:10px;"
		"background-color:rgb(4,167,240);color:white;font-size:25px}");
	toolButton_4->setStyleSheet("border:2px groove gray;border-radius:10px;"
		" background-color:rgb(4,167,240);color:white;font-size:25px");
	toolButton_5->setStyleSheet("QToolButton{border:2px groove white;border-radius:10px;"
		"background-color:rgb(4,167,240);color:white;font-size:25px}");
	toolButton_6->setStyleSheet("QToolButton{border:2px groove white;border-radius:10px;"
		"background-color:rgb(4,167,240);color:white;font-size:25px}");
	toolButton_7->setStyleSheet("QToolButton{border:2px groove white;border-radius:10px;"
		"background-color:rgb(4,167,240);color:white;font-size:25px}");
	toolButton_8->setStyleSheet("border:2px groove gray;border-radius:10px;"
		" background-color:rgb(4,167,240);color:white;font-size:25px");
	toolButton_9->setStyleSheet("QToolButton{border:2px groove white;border-radius:10px;"
		"background-color:rgb(4,167,240);color:white;font-size:25px}");
	toolButton_backspace->setStyleSheet("border:2px groove gray;border-radius:10px;"
		" background-color:rgb(4,167,240);color:white;font-size:25px");
	toolButton_enter->setStyleSheet("QToolButton{border:2px groove white;border-radius:10px;"
		"background-color:rgb(4,167,240);color:white;font-size:25px}");


}

void NumKeyBoard::Init(WIDGET_TYPE types)
{
	m_type = types;
	if (types & MSGBOX_GET)
	{
		label_title->setStyleSheet("min-width:379px;"
								   "max-width:379px;"
		                           "min-height:71px;"
								   "max-height:71px;"
								   "border-image: url(:/Image/Resources/Image/������ȡ����.png);");
	}
	if (types & MSGBOX_SAVE)
	{
		label_title->setStyleSheet("min-width:379px;"
								   "max-width:379px;"
								   "min-height:71px;"
			                       "max-height:71px;"
			                       "border-image: url(:/Image/Resources/Image/����������.png);");
	}
}

void NumKeyBoard::setMapper()
{
	//number
	signalMapper->setMapping(toolButton_0, toolButton_0->text());
	signalMapper->setMapping(toolButton_1, toolButton_1->text());
	signalMapper->setMapping(toolButton_2, toolButton_2->text());
	signalMapper->setMapping(toolButton_3, toolButton_3->text());
	signalMapper->setMapping(toolButton_4, toolButton_4->text());
	signalMapper->setMapping(toolButton_5, toolButton_5->text());
	signalMapper->setMapping(toolButton_6, toolButton_6->text());
	signalMapper->setMapping(toolButton_7, toolButton_7->text());
	signalMapper->setMapping(toolButton_8, toolButton_8->text());
	signalMapper->setMapping(toolButton_9, toolButton_9->text());
	
	
}

void NumKeyBoard::connectMapper()
{
	connect(toolButton_0, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(toolButton_1, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(toolButton_2, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(toolButton_3, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(toolButton_4, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(toolButton_5, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(toolButton_6, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(toolButton_7, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(toolButton_8, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(toolButton_9, SIGNAL(clicked()), signalMapper, SLOT(map()));


}

void NumKeyBoard::setDispText(const QString &text)
{
	if (waitingForOperand)
	{
		display->clear();
		waitingForOperand = false;
	}
	display->insert(text);
}

void NumKeyBoard::onEnter()
{

	waitingForOperand = true;
	text = display->text();
	int i = text.indexOf("-");
	if (text.length()!=6 || i!=-1)
	{
		QMessageBox::about(nullptr, "onEnter", "������ַ�����");
		return;
	}

	display->clear();
	text.replace("-", "");
	m_nInputNum = text.toInt();
	gblRuntimeData->InputNum = text.toInt();
	if (m_type & MSGBOX_GET)
	{
		AppInfo app;
		bool bres = gblControlSql->Get_App_By_QRnum(m_nInputNum, app);
		if (bres == false)
		{
			QMessageBox::about(nullptr, "����", "�˶�ά�벻���ڣ�");
			return ;
		}
	}
	if (m_type & MSGBOX_SAVE)
	{			
		AppInfo app;
		bool bres = gblControlSql->Get_App_By_QRnum(m_nInputNum, app);
		if (bres == true)
		{
			QMessageBox::about(nullptr, "����", "�˶�ά����ʹ�ã�");
			return ;
		}
		app.saveQRNum = m_nInputNum;
		for (int nRow = MAXNULLTRAY; nRow < MAXROW;)
		{
			for (int nColumn = 0; nColumn < MAXCOLUMN; nColumn++)
			{
				AppInfo Info;
				bool bresult = gblControlSql->Get_App_By_Point(nRow, nColumn, Info);
				if (bresult == false)
				{
					app.savePoint.setX(nRow);
					app.savePoint.setY(nColumn);
					gblControlSql->Add_AppInfo(app);				
					gblPortControl->MovePoint(nRow, nColumn);
					m_bSecond = false;
					return ;
				}
			}
			nRow += ADDROW;
		}
	}





}
void NumKeyBoard::on_slot_MoveFinish()
{
	if (m_type & MSGBOX_GET)
	{
	
	}
	if (m_type & MSGBOX_SAVE)
	{
		if (m_bSecond == false)
		{
			gblPortControl->PushGoods();
		}
		else
		{
			gblPortControl->PushGoods();
		}
	
	}
}
void NumKeyBoard::on_slot_PushGoodsFinish()
{
	if (m_type & MSGBOX_GET)
	{
		
	}
	if (m_type & MSGBOX_SAVE)
	{
		if (m_bSecond == false)
		{
			gblPortControl->SuckTray();
		}
		else
		{
			gblPortControl->DropTray();
		}
	}
}
void NumKeyBoard::on_slot_SuckTrayFinish()
{
	if (m_type & MSGBOX_GET)
	{
	}
	if (m_type & MSGBOX_SAVE)
	{
		if (m_bSecond == false)
		{
			gblPortControl->GetGoods();
		}
	}
}
void NumKeyBoard::on_slot_DropTrayFinish()
{
	if (m_type & MSGBOX_GET)
	{
	}
	if (m_type & MSGBOX_SAVE)
	{
		gblPortControl->OpenDoor();
	}
}

void NumKeyBoard::on_slot_GetGoodsFinish()
{
	if (m_type & MSGBOX_GET)
	{
	
	}
	if (m_type & MSGBOX_SAVE)
	{
		if (m_bSecond == false)
		{
			gblPortControl->MovePoint(0, 0);
			m_bSecond = true;
		}
	}
}


void NumKeyBoard::on_slot_OpendoorFinish()
{
	if (m_type & MSGBOX_GET)
	{
	}
	if (m_type & MSGBOX_SAVE)
	{
		done(text.toInt());
	}
}
void NumKeyBoard::on_slot_ClosedoorFinish()
{
}
void NumKeyBoard::onBackspace()
{
	display->backspace();
}
/*֧�������ק����*/
void NumKeyBoard::mouseMoveEvent(QMouseEvent *event)
{
	return QDialog::mouseMoveEvent(event);
	if (event->buttons() == Qt::LeftButton)
	{
		move(event->globalPos() - dragPosition);
		event->accept();
	}
}

void NumKeyBoard::mousePressEvent(QMouseEvent *event)
{
	return QDialog::mousePressEvent(event);
	if (event->button() == Qt::LeftButton)
	{
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
	if (event->button() == Qt::RightButton)
	{
		close();
	}
}

void NumKeyBoard::onInvMode()
{
	if (inputMode == iMode_Normal)
	{
		inputMode = iMode_Passwd;
	}
	else if (inputMode == iMode_Passwd)
	{
		inputMode = iMode_Normal;
	}

	if (inputMode == iMode_Normal)
	{
		display->setEchoMode(QLineEdit::Normal);
	}
	else if (inputMode == iMode_Passwd)
	{
		display->setEchoMode(QLineEdit::Password);
	}
}

void NumKeyBoard::on_slot_textChanged(const QString & text)
{
	for (int i=0;i<text.length();i++)
	{
		QString num = text.at(i);
		QString lcdname = QString("label_%1").arg(i+1);
		QLabel *db = this->findChild<QLabel *>(lcdname);
		if (db!=nullptr)
		{
			db->setText(num);
		}
	}
	for (int i = text.length(); i < 6; i++)
	{
		QString lcdname = QString("label_%1").arg(i+1);
		QLabel *db = this->findChild<QLabel *>(lcdname);
		if (db != nullptr)
		{
			QString num = "-";		
			db->setText(num);
		}
	}
}

void NumKeyBoard::on_btnBack_clicked()
{
	done(WIDGET_TYPE::MSGBOX_BACK);
}

void NumKeyBoard::on_btnHome_clicked()
{
	done(MSGBOX_HOME);
}
