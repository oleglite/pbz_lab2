#include "custominputdialog.h"

CustomInputDialog::CustomInputDialog(const QStringList &inputsLabels, QWidget *parent) :
    mInputsLabels(inputsLabels),
    QDialog(parent)
{
    QGridLayout* layout = new QGridLayout;
    layout->setColumnStretch(1, 0);
    for(int i = 0; i < mInputsLabels.size(); i++) {
        layout->addWidget(new QLabel(mInputsLabels.value(i)), i, 0, Qt::AlignRight);
        mEdits << new QLineEdit;
        layout->addWidget(mEdits.last(), i, 1);
    }

    mButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(mButtons, SIGNAL(accepted()), SLOT(accept()));
    connect(mButtons, SIGNAL(rejected()), SLOT(reject()));

    layout->addWidget(mButtons, 4, 1);

    setLayout(layout);
}

QStringList CustomInputDialog::showDialog(const QStringList& inputsLabels)
{
    QStringList result;
    CustomInputDialog dialog(inputsLabels);
    if(dialog.exec() == QDialog::Accepted) {
        for(int i = 0; i < inputsLabels.size(); i++) {
            result << dialog.mEdits.value(i)->text();
        }
    }
    return result;
}
