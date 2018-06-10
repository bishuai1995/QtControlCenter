#ifndef SQLBASE_H
#define SQLBASE_H
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include <QObject>

#include <QString>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QtSql/QSqlDatabase>
#include <QQueue>


#include <QReadWriteLock>

#include "log/log_deffine.h"

#include "Lock_Tool.h"


/*
NOT NULL - �ǿ� 
UNIQUE - Ψһ 
PRIMARY KEY - ���� 
FOREIGN KEY - ��� 
CHECK - ������� 
DEFAULT - Ĭ��
*/


class  CSQLBase : public QObject
{
	Q_OBJECT
public:
	explicit CSQLBase(QObject *parent = 0);
	~CSQLBase();

	/* �������ݿ���.*/
	void SetTableName(QString dbName,QString strTableName);

	/* �����ݿ�.*/
	bool opendatabase();

	/* �������.

	CREAT TABLE IF NOT EXISTS + ����(strTableName)  + (strExpreesion,strExpreesion,strExpreesion)
	*/
	bool CreatTable(QString strTableName, QStringList strExpreesion);

	/* �������.*/
	bool CreatTableEx(QString strTableName, QStringList strExpreesion);

	/* �������.
	CREAT TABLE IF NOT EXISTS + (����)strTableName  + strExpreesion
	*/
	bool CreatTable(QString strTableName,QString strExpreesion);

	/* ���������.
	ALTER TABLE +�ɱ���+ RENAME TO + strTableName (����) 
	*/
	bool RenameTable(QString strTableName);

	/* ���ĳ���Ƿ����.
	//ALTER TABLE ���� ADD COLUMN + strColumnName (���� �������� �޶���)
	*/
	bool TableIsColumnExist(QString &strColumnName);

	/* �������һ��.
	//ALTER TABLE ���� ADD COLUMN + strExpreesion (���� �������� �޶���)
	*/
	bool TableAddColumn(QString &strExpreesion);

	/* ɾ�����.
	 ɾ���� - DROP TABLE +strTableName (����)
	*/
	bool DropTable(QString strTableName);

	/* ���뺯��. ����SQL�������.
	insert into (names,names,names) values (values,values,values)
	*/
	bool Insert(QStringList &strNames,QStringList &strValues);



	/* �޸ĺ���. ����SQL�޸����.
	UPDATE ������ SET (names,names,names) = (values,values,values) WHERE strExpreesion
	*/
	bool Update(QStringList &strNames,QStringList &strValues, QString &strExpreesion);



	/* ɾ������.����SQLɾ�����.
	//DELETE FROM ������ WHERE strExpreesion
	*/
	bool Delete(QString &strExpreesion);

	/* ɾ������.����SQLɾ�����.
	//DELETE FROM ������ WHERE strKeys =strValues and strKeys =strValues
	*/
	bool Delete(QStringList &strKeys,QStringList &strValues);

	/*ִ�����ݿ����ԣ�select��insert��update,delete,Ҳ����ִ�д洢���̺ʹ洢����.
	����strExpreesion �����
	*/
	BOOL dbExecSql(QString strExpreesion);

	/* ���Һ���.����SQL��ѯ���.
	select * from ������ 
	���� ��һ����Ϣ
	*/
	void GetValues(QStringList &strReturnValues);

	/* ���Һ���.����SQL��ѯ���.
	select * from ������ + where + strExpreesion 
	���� ��nValues����Ϣ
	*/
	void GetValues(QStringList &strReturnValues,QString &strExpreesion,int nValues);

	/* ���Һ���.����SQL��ѯ���.*/
	void GetValues(QStringList &strName,QStringList &strValues,QString &strExpreesion,int nValues);

	/* ���Һ���.����SQL��ѯ���.
	select * from ������ + where  key = values ,key= values  ,��������ѯ���� strKeys.sizeΪ0
	���ؽ����
	*/
	QQueue < QSqlRecord >  GetValues(QStringList &strKeys,QStringList &strValues);

	/* ���Һ���.��ѯ�������.*/
	int TableCount();

	/* ��ʼ������.*/
	void InitQstringList(QStringList &strName,QStringList &strValues);




	/*ִ�����ݿ����ԣ�select��insert��update,delete,Ҳ����ִ�д洢���̺ʹ洢����.
	strSql���������  rows �����������������
	cols�� �����������������RecordQueue����������
	���أ�	TURE: ִ�гɹ�
	 False:ʧ��
	*/
	int dbExecSql( QString strSql,int &rows,int &cols,std::vector< QSqlRecord > &pRecordQueue);


	QQueue < QSqlRecord > ReadAppData();

public:
	QSqlTableModel	*model;
	QSqlDatabase	m_db;
	QString			m_strTableName;			//�����
	QString			m_strDbName;		    //���ݿ���
	QString         m_strError;
	//QReadWriteLock m_mutex;
	 


	_LOCK_KEY_;
};







#endif // SQLBASE_H
