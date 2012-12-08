#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_customRequestDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mDB(0),
    mUi(new Ui::MainWindow),
    mCustomRequestDialogUi(new Ui::CustomRequestDialog),
    mCustomRequestDialog(new QDialog),
    mFileDialog(new QFileDialog),
    mCentralTableView(new QTableView)
{
    mUi->setupUi(this);
    mCustomRequestDialogUi->setupUi(mCustomRequestDialog);
    mFileDialog->setDirectory(QDir("D:/"));
    setCentralWidget(mCentralTableView);

    connect(mUi->open, SIGNAL(triggered()), SLOT(showDialogOpenDB()));
    connect(mUi->customRequest, SIGNAL(triggered()), SLOT(showDialogCustomRequest()));
    connect(mFileDialog, SIGNAL(fileSelected(QString)), SLOT(openDB(QString)));
    connect(mCustomRequestDialog, SIGNAL(accepted()), SLOT(customRequest()));
}

MainWindow::~MainWindow()
{
    delete mUi;
    delete mCustomRequestDialogUi;
    delete mCustomRequestDialog;
    if(mDB)
        delete mDB;
}

void MainWindow::showDialogOpenDB()
{
    mFileDialog->show();
}

void MainWindow::openDB(const QString& filePath)
{
    if(mDB) {
        delete mDB;
    }
    mDB = new Database(filePath);
    mCentralTableView->setModel(mDB->getModel());
    createActions();
}

void MainWindow::showDialogCustomRequest()
{
    mCustomRequestDialog->show();
}

void MainWindow::customRequest()
{
    mDB->customRequest(mCustomRequestDialogUi->textEdit->toPlainText());
}

void MainWindow::createActions()
{
    mUi->menuQuery->clear();
    foreach(const DatabaseQuery& databaseQuery, mDB->getQueries()) {
        createQueryAction(databaseQuery.desc);
    }
}

void MainWindow::createQueryAction(const QString& queryDesc)
{
    QAction *action = mUi->menuQuery->addAction(queryDesc);
    ActionHandler *handler = new ActionHandler(action);
    connect(action, SIGNAL(triggered()), handler, SLOT(actionTriggered()));
    connect(handler, SIGNAL(triggered(QString)), mDB, SLOT(request(QString)));
}
