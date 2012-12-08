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

    void customRequest(const QString&);
    QSqlQueryModel* getModel();

    const QList<DatabaseQuery>& getQueries() const;
    QStringList getTables() const;

public slots:
    void request(const QString& queryDesc);


private:
    QSqlQueryModel mSqlModel;
    QList<DatabaseQuery> mQueries;
    QSqlDatabase mDatabase;

    void loadQueries(const QString&);
};

#endif // DATABASE_H
