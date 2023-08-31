#include <iostream>

#include "DataBase.h"
#include <memory>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlRecord>

bool DataBase::connect(QString host, unsigned int port, QString dbname, QString user, QString password)
{
    _mysql = QSqlDatabase::addDatabase("QODBC");
    _mysql.setHostName("127.0.0.1");//host
    _mysql.setPort(3306);//port
    _mysql.setDatabaseName(QString("DRIVER={MySQL ODBC 8.1 ANSI Driver};DBQ='%1'").
                           arg("chat1"));//dbname
    _mysql.setUserName("root");//user
    _mysql.setPassword("Kooko_099");//password
    if (!_mysql.open()){
        _connection = false;
        QMessageBox::warning(nullptr, "Error", _mysql.lastError().text());
   }
    else {
        _connection = true;
        qDebug("success");
        executeQueryWithoutResult("use chat1;");
    }
	return _connection;
}

bool DataBase::hasConnection()
{
	return _connection;
}

QVector<QString> DataBase::queryResult(QString queryText)
{
    QVector<QString> result;
    QSqlQuery query(_mysql);
    query.prepare(queryText);
    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", query.lastError().text());
    }
    while (query.next()) {
        int count = query.record().count();
        for (int i = 0; i < count; i++) {
            result.push_back(query.value(i).toString());
        }
    }

	return result;
}

void DataBase::executeQueryWithoutResult(QString queryText)
{
    QSqlQuery query(_mysql);
    query.prepare(queryText);
    if (!query.exec()) {
        QMessageBox::warning(nullptr, "Error", query.lastError().text());
    }
}

void DataBase::close()
{
    _mysql.close();
}

DataBase::DataBase()
{
    _connection = false;
}

DataBase::~DataBase()
{
	close();
}
