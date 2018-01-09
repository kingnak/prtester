#include "prtesterwidget.h"
#include "ui_prtesterwidget.h"

PRTesterWidget::PRTesterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PRTesterWidget)
{
    ui->setupUi(this);
}

PRTesterWidget::~PRTesterWidget()
{
    delete ui;
}

void PRTesterWidget::on_btnStart_clicked()
{
    ui->wgtTest->setTester(ui->wgtSetup->getTester());
    ui->stkMain->setCurrentWidget(ui->pageTest);
    ui->wgtTest->firstQuestion();
}

void PRTesterWidget::on_btnBack_clicked()
{
    ui->stkMain->setCurrentWidget(ui->pageSetup);
}
