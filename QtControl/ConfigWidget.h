#pragma once

#include <QWidget>
#include "ui_ConfigWidget.h"
#include "CMainWidget.h"
class ConfigWidget : public QWidget,public Ui::ConfigWidget
{
	Q_OBJECT

public:
	ConfigWidget(QWidget *parent = Q_NULLPTR);
	~ConfigWidget();

public slots :
	void on_slot_Ok();


public:
	CMainWidget * uesrWidget;

};
