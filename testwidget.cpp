#include "testwidget.h"
#include "ui_testwidget.h"
#include <QMessageBox>

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget),
    m_total(0),
    m_correct(0)
{
    ui->setupUi(this);
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::nextQuestion()
{
    m_total++;
    ui->txtStat->setText(QString("%1/%2").arg(m_correct).arg(m_total));
    ui->btnNext->setVisible(false);
    ui->lblSolution->setVisible(false);
    ui->lblWrong->setVisible(false);
    ui->btnSolve->setVisible(false);
    m_question = m_tester.nextQuestion();
    ui->txtQuestion->setText(m_question.question());
    ui->txtAnswer->clear();
    ui->txtAnswer->setFocus();
    ui->lblSolution->setText(m_question.answer());
}

void TestWidget::firstQuestion()
{
    m_total = m_correct = 0;
    nextQuestion();
}

void TestWidget::checkAnswer()
{
    if (m_question.verify(ui->txtAnswer->text())) {
        m_correct++;
        nextQuestion();
    } else {
        ui->lblWrong->setVisible(true);
        ui->btnSolve->setVisible(true);
    }
}

void TestWidget::on_btnSolve_clicked()
{
    ui->lblSolution->setVisible(true);
    ui->btnSolve->setVisible(false);
    ui->btnNext->setVisible(true);
}

void TestWidget::on_btnNext_clicked()
{
    nextQuestion();
}
