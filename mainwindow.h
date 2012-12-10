#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "database.h"
#include "actionhandler.h"

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
    
private:
    Database *mDB;

    Ui::MainWindow *mUi;
    Ui::CustomRequestDialog *mCustomRequestDialogUi;

    QDialog *mCustomRequestDialog;
    QFileDialog *mFileDialog;
    QTableView *mCentralTableView;


    void createActions();
    void createQueryAction(const QString &queryDesc);
    void createTableAction(const QString &tableName);
};

#endif // MAINWINDOW_H
