#pragma once
#include "Base/SQLBase.h"
#include <QSqlError>
#include <QSqlRecord>
#include <QObject>
#include <QList>
#include <QVector>
#include "define.h"
#include "include/HSingleton/HSingleton.h"


class ControlSql : public CSQLBase
{
	Q_OBJECT

public:
	ControlSql(QObject *parent=nullptr);
	~ControlSql();

public:

	void  InitSQL();

	/*���뺯��. ����SQL�������.
	insert into (info.names,info.names,info.names) values (info.values,info.values,info.values)
	*/
	bool Insert(AppInfo &info);

	/* �޸ĺ���. ����SQL�޸����.
	UPDATE ������ SET (info.names,info.names,info.names) = (info.values,info.values,info.values) WHERE strExpreesion
	*/
	bool Update(AppInfo &info, QString &strExpreesion);

	/*���ݰ�*/
	void BindValues(QSqlQuery &query, AppInfo info);

	void Read_AppList();
	//����һ��APP
	void Add_AppInfo(AppInfo &info);
	//����һ��APP
	void Update_AppInfo(AppInfo &info);
	//ɾ��һ��APP
	void Delete_AppInfo(AppInfo &info);


	bool Get_App_By_QRnum(int nQRnum, AppInfo& Info);

	bool Get_App_By_Point(int nRow,int nColoumn, AppInfo& Info);

	/*�ѻ�ȡ����Ϣ д�� info��Ϣ
	query  ���ص����ݿ�����  info:д��info��Ϣ
	*/
	void WriteValues(QSqlRecord &query, AppInfo &info);
public:
	QList<AppInfo>   m_AppList;


	QVector<QPoint>   vecAppId;	//���ڵ�IDֵ
};

#define gblControlSql   HSingletonTemplatePtr<ControlSql>::get()