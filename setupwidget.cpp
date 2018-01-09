#include "setupwidget.h"
#include "ui_setupwidget.h"
#include "prtester.h"
#include "prdata.h"
#include <QListWidget>

SetupWidget::SetupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupWidget)
{
    ui->setupUi(this);

    setupList(ui->lstCycles, PRData::instance().cycleNames());
    setupList(ui->lstGrandCycles, PRData::instance().grandCycleNames());
}

SetupWidget::~SetupWidget()
{
    delete ui;
}

PRTester SetupWidget::getTester()
{
    PRTester t;
    if (ui->chkAnswerNr->isChecked()) t.askNumber();
    if (ui->chkAnswerTitle->isChecked()) t.askTitle();
    if (ui->radAskAll->isChecked()) t.byAll();
    if (ui->radAskGrandCycles->isChecked()) t.byGrandCycles(checkedItems(ui->lstGrandCycles));
    if (ui->radAskCycles->isChecked()) t.byCycles(checkedItems(ui->lstCycles));
    return t;
}

void SetupWidget::checkCanStart()
{
    bool ok = true;
    if (!ui->chkAnswerNr->isChecked() && !ui->chkAnswerTitle->isChecked()) {
        ok = false;
    }

    if (ui->radAskCycles->isChecked()) {
        if (checkedItems(ui->lstCycles).isEmpty())
            ok = false;
    }
    if (ui->radAskGrandCycles->isChecked()) {
        if (checkedItems(ui->lstGrandCycles).isEmpty())
            ok = false;
    }

    emit canStart(ok);
}

void SetupWidget::setupList(QListWidget *lst, const QStringList &items)
{
    lst->clear();
    for (auto i : items) {
        QListWidgetItem *itm = new QListWidgetItem(i);
        itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
        itm->setCheckState(Qt::Checked);
        lst->addItem(itm);
    }
}

QList<int> SetupWidget::checkedItems(QListWidget *lst)
{
    QList<int> ret;
    for (int i = 0; i < lst->count(); ++i) {
        if (lst->item(i)->checkState() == Qt::Checked) {
            ret << i;
        }
    }

    return ret;
}
