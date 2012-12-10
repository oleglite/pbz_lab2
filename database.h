#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QObject>

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

    void customRequest(const QString&);

public slots:
    /** ¬ыполнить готовый запрос
     * @param queryDesc описание запроса
     */
    void loadedRequest(const QString& queryDesc);
    void tableRequest(const QString& tableName);

private:
    QSqlQueryModel mSqlModel;
    QList<DatabaseQuery> mQueries;
    QSqlDatabase mDatabase;

    static QStringList splitComplexQuery(const QString&);
    void loadQueries(const QString&);
    void transaction(const QStringList&);
};

#endif // DATABASE_H
