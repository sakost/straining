#include "configurecomplexesdialog.h"
#include "ui_configurecomplexesdialog.h"

#include <QSizePolicy>

ConfigureComplexesDialog::ConfigureComplexesDialog(const QVector< QPair<ComplexInterface*, bool> >& complexes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureComplexesDialog)
{
    ui->setupUi(this);

    this->complexes = QVector<QCheckBox*>();
    QVBoxLayout *vLayout = this->ui->verticalLayout_2;
    vLayout->setAlignment(Qt::AlignTop);
    for(auto &el: complexes){
        QHBoxLayout *hLayout = new QHBoxLayout;
        QCheckBox* checkBox = new QCheckBox(el.first->uName);
        checkBox->setChecked(el.second);
        hLayout->addWidget(checkBox);
        hLayout->setSizeConstraint(QLayout::SetMinimumSize);
        vLayout->addLayout(hLayout);
    }
}

ConfigureComplexesDialog::~ConfigureComplexesDialog()
{
    delete ui;
}

void ConfigureComplexesDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
