#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QObject>

#include "custominputdialog.h"

struct DatabaseQuery
{
    DatabaseQuery(const QString& d) :
        desc(d)
    {}

    QString desc;
    QString request;
};

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(const QString& dbFilePath);

    QSqlQueryModel* getModel();
    const QList<DatabaseQuery>& getLoadedQueries() const;
    QStringList getTablesNames() const;

    void performCustomRequest(const QString&);
    QSqlTableModel *performTableRequest(const QString& tableName);

public slots:
    /** ¬ыполнить готовый запрос
     * @param queryDesc описание запроса
     */
    void performLoadedRequest(const QString& queryDesc);
    void update();

private:
    QSqlQueryModel mSqlModel;
    QList<DatabaseQuery> mQueries;
    QSqlDatabase mDatabase;
    QList<QSqlTableModel*> mTableModels;

    static bool requestHasInputs(const QString &request);
    static bool isComplexRequest(const QString &request);

    static QStringList splitComplexQuery(const QString&);
    void loadQueries(const QString&);

    static QSqlQuery performTtransaction(const QStringList &queries);
    static QSqlQuery performInputRequest(const QString &request);
};

#endif // DATABASE_H
