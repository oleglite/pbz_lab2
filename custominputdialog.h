#ifndef CUSTOMINPUTDIALOG_H
#define CUSTOMINPUTDIALOG_H

#include <QtGui>

class CustomInputDialog : public QDialog
{
    Q_OBJECT
public:
    friend class CustomInputDialog;
    static QStringList showDialog(const QStringList& inputsLabels);
    
private:
    CustomInputDialog(const QStringList& inputsLabels, QWidget *parent = 0);

    QStringList mInputsLabels;
    QList<QLineEdit*> mEdits;
    QDialogButtonBox* mButtons;
};

#endif // CUSTOMINPUTDIALOG_H
