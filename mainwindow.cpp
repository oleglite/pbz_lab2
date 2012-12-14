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
    mCentralLabel(new QLabel),
    mCentralTableView(new QTableView)
{
    mUi->setupUi(this);
    mCustomRequestDialogUi->setupUi(mCustomRequestDialog);
    mFileDialog->setDirectory(QDir("D:/"));

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(mCentralLabel);
    centralLayout->addWidget(mCentralTableView);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

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
    mCentralLabel->clear();
}

void MainWindow::showDialogCustomRequest()
{
    mCustomRequestDialog->show();
}

void MainWindow::customRequest()
{
    mDB->performCustomRequest(mCustomRequestDialogUi->textEdit->toPlainText());
    mCentralLabel->clear();
}

void MainWindow::setCentralLabel(const QString& labelText)
{
    mCentralLabel->setText(labelText);
}

void MainWindow::tableRequest(const QString& tableName)
{
    QTableView *view = new QTableView();
    view->setModel(mDB->performTableRequest(tableName));
    view->setWindowTitle(tableName);
    view->resizeColumnsToContents();
    view->resize(view->horizontalHeader()->length() + 30, view->verticalHeader()->length() + 40);
    view->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    QApplication::exit();
}

void MainWindow::createActions()
{
    mUi->menuQuery->clear();
    foreach(const DatabaseQuery& databaseQuery, mDB->getLoadedQueries()) {
        createQueryAction(databaseQuery.desc);
    }
    mUi->menuTable->clear();
    foreach(const QString& tableName, mDB->getTablesNames()) {
        createTableAction(tableName);
    }
}

void MainWindow::createQueryAction(const QString& queryDesc)
{
    QAction *action = mUi->menuQuery->addAction(queryDesc);
    ActionHandler *handler = new ActionHandler(action);
    connect(action, SIGNAL(triggered()), handler, SLOT(actionTriggered()));
    connect(handler, SIGNAL(triggered(QString)), mDB, SLOT(performLoadedRequest(QString)));
    connect(handler, SIGNAL(triggered(QString)), SLOT(setCentralLabel(QString)));
}

void MainWindow::createTableAction(const QString &tableName)
{
    QAction *action = mUi->menuTable->addAction(tableName);
    ActionHandler *handler = new ActionHandler(action);
    connect(action, SIGNAL(triggered()), handler, SLOT(actionTriggered()));
    connect(handler, SIGNAL(triggered(QString)), SLOT(tableRequest(QString)));
    connect(handler, SIGNAL(triggered(QString)), SLOT(setCentralLabel(QString)));
}

