#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <QObject>
#include <QAction>

class ActionHandler : public QObject
{
    Q_OBJECT
public:
    explicit ActionHandler(QAction *action);

signals:
    void triggered(QString);
    
public slots:
    void actionTriggered();

private:
    QAction *mAction;
};

#endif // ACTIONHANDLER_H
