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

void Database::performLoadedRequest(const QString &queryDesc)
{
    foreach(DatabaseQuery dq, mQueries) {
        if(dq.desc == queryDesc) {
            performCustomRequest(dq.request);
        }
    }
}

void Database::performTableRequest(const QString& tableName)
{
    performCustomRequest("SELECT * FROM " + tableName + ";");
}

void Database::performCustomRequest(const QString& request)
{
    if(isComplexRequest(request)) {
        const QSqlQuery& query = performTtransaction(splitComplexQuery(request));
        mSqlModel.setQuery(query);
    } else if(requestHasInputs(request)) {
        mSqlModel.setQuery(performInputRequest(request));
    } else {
        mSqlModel.setQuery(request);
    }
}

bool Database::requestHasInputs(const QString& request)
{
    return request.indexOf(":") >= 0;
}

bool Database::isComplexRequest(const QString &request)
{
    return request.indexOf(";", request.indexOf(";") + 1) >= 0;
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

QSqlQuery Database::performTtransaction(const QStringList& queries)
{
    qDebug() << "transaction()" << queries;

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    foreach(QString q, queries) {
        if(requestHasInputs(q)) {
            query = performInputRequest(q);
        } else {
            query.exec(q);
        }
    }
    QSqlDatabase::database().commit();
    return query;
}

QSqlQuery Database::performInputRequest(const QString& request)
{
    QSqlQuery query;
    query.prepare(request);

    QStringList placeHolders;
    QStringList inputValuesLabels;
    QRegExp rx(":(\\w+)");
    int pos = 0;
    while ((pos = rx.indexIn(request, pos)) != -1) {
        pos += rx.matchedLength();
        placeHolders << rx.cap(0);
        inputValuesLabels << rx.cap(1);
    }

    const QStringList& values = CustomInputDialog::showDialog(inputValuesLabels);
    if(values.size() == placeHolders.size()) {
        for(int i = 0; i < values.size(); i++) {
            query.bindValue(placeHolders.value(i), values.value(i));
        }
        query.exec();
        return query;
    } else {
        return QSqlQuery();
    }

}

