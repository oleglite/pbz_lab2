#include "actionhandler.h"

ActionHandler::ActionHandler(QAction *action) :
    mAction(action),
    QObject(action)
{
}

void ActionHandler::actionTriggered()
{
    emit triggered(mAction->text());
}
