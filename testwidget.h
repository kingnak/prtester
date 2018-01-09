#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "prtester.h"

namespace Ui {
class TestWidget;
}

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidget(QWidget *parent = 0);
    ~TestWidget();

    void setTester(const PRTester &t) { m_tester = t; }

public slots:
    void nextQuestion();
    void firstQuestion();

private slots:
    void checkAnswer();
    void on_btnSolve_clicked();
    void on_btnNext_clicked();

private:
    Ui::TestWidget *ui;

    PRTester m_tester;
    PRTester::Question m_question;

    int m_total;
    int m_correct;
};

#endif // TESTWIDGET_H
