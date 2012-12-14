#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "database.h"
#include "actionhandler.h"
#include "custominputdialog.h"

namespace Ui {
class MainWindow;
class CustomRequestDialog;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showDialogOpenDB();
    void openDB(const QString& filePath);
    void showDialogCustomRequest();
    void customRequest();
    void setCentralLabel(const QString&);
    void tableRequest(const QString &tableName);

protected:
    void closeEvent(QCloseEvent *);
    
private:
    Database *mDB;

    Ui::MainWindow *mUi;
    Ui::CustomRequestDialog *mCustomRequestDialogUi;

    QDialog *mCustomRequestDialog;
    QFileDialog *mFileDialog;
    QLabel *mCentralLabel;
    QTableView *mCentralTableView;


    void createActions();
    void createQueryAction(const QString &queryDesc);
    void createTableAction(const QString &tableName);
};

#endif // MAINWINDOW_H
