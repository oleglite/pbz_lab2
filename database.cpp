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
    qDebug() << getTables();

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

const QList<DatabaseQuery>& Database::getQueries() const
{
    return mQueries;
}

QStringList Database::getTables() const
{
    QRegExp tableFilter("[A-Z]{1}([a-z]?)*");
    tableFilter.setCaseSensitivity(Qt::CaseSensitive);
    return mDatabase.tables(QSql::Tables).filter(tableFilter);
}

void Database::request(const QString &queryDesc)
{
    foreach(DatabaseQuery dq, mQueries) {
        if(dq.desc == queryDesc) {
            customRequest(dq.request);
        }
    }
}

void Database::customRequest(const QString& request)
{
    mSqlModel.setQuery(request);
}

