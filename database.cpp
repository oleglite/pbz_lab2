#include "database.h"

#include <QDebug>

Database::Database(const QString& dbFilePath):
    QObject(0),
    mDatabase(QSqlDatabase::addDatabase("QSQLITE"))
{
    mDatabase.setDatabaseName(dbFilePath);

    if (!mDatabase.open()) {
        qDebug() << mDatabase.lastError().text();
    }

    loadQueries("D:\\Documents\\univer\\term 5\\PBZ\\lab2\\queries.sql");
    qDebug() << getTablesNames();

/*
    QSqlQuery query("SELECT * FROM Cutter");
    qDebug() << query.isActive();
    while (query.next()) {
        qDebug() << query.value(0).toString() << query.value(1).toString();
    }*/
}

void Database::loadQueries(const QString& filename)
{
    mQueries.clear();

    QFile queriesFile(filename);
    if (!queriesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can't open queries file";
        return;
    }

    QTextStream textStream(&queriesFile);
    while (!textStream.atEnd()) {
        QString line = textStream.readLine();
        if(line.startsWith("--")) {
            mQueries << DatabaseQuery(line.mid(2).trimmed());
        } else {
            if(!mQueries.isEmpty()) {
                mQueries.last().request.append(line + "\n");
            }
        }
    }

    foreach(DatabaseQuery dq, mQueries) {
        qDebug() << dq.desc << dq.request;
    }

    queriesFile.close();
}

QSqlQueryModel* Database::getModel()
{
    return &mSqlModel;
}

const QList<DatabaseQuery>& Database::getLoadedQueries() const
{
    return mQueries;
}

QStringList Database::getTablesNames() const
{
    QRegExp tableFilter("[A-Z]{1}([a-z]?)*");
    tableFilter.setCaseSensitivity(Qt::CaseSensitive);
    return mDatabase.tables(QSql::Tables).filter(tableFilter);
}

void Database::loadedRequest(const QString &queryDesc)
{
    foreach(DatabaseQuery dq, mQueries) {
        if(dq.desc == queryDesc) {
            customRequest(dq.request);
        }
    }
}

void Database::tableRequest(const QString& tableName)
{
    customRequest("SELECT * FROM " + tableName + ";");
}

void Database::customRequest(const QString& request)
{
    if(request.indexOf(";", request.indexOf(";") + 1) >= 0) {
        transaction(splitComplexQuery(request));
    }
    mSqlModel.setQuery(request);
    qDebug() << "customRequest()" << mSqlModel.query().isActive() << mSqlModel.query().executedQuery();
    qDebug() << "==============================";
    qDebug() << request;
    qDebug() << "==============================";

}

QStringList Database::splitComplexQuery(const QString& q)
{
    QStringList resultQueries;
    QString query = q;
    while(!query.isEmpty() && query.indexOf(";") >= 0) {
        int queryLength = query.indexOf(";") + 1;
        resultQueries << query.mid(0, queryLength);
        query.remove(0, queryLength);
    }
    return resultQueries;
}

void Database::transaction(const QStringList& queries)
{
    qDebug() << "transaction()" << queries;

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    foreach(QString q, queries) {
        query.exec(q);
    }
    QSqlDatabase::database().commit();
    mSqlModel.setQuery(query);
}

