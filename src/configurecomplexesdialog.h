#pragma once

#include <QDialog>
#include <QGroupBox>
#include <QBoxLayout>
#include <QCheckBox>

#include "complexinterface.h"

namespace Ui {
class ConfigureComplexesDialog;
}

class ConfigureComplexesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureComplexesDialog(const QVector< QPair<ComplexInterface*, bool> >& complexes, QWidget *parent = nullptr);
    ~ConfigureComplexesDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ConfigureComplexesDialog *ui;
    QVector< QCheckBox* > complexes;
};

