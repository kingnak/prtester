#ifndef PRTESTERWIDGET_H
#define PRTESTERWIDGET_H

#include <QWidget>
#include "prdata.h"

namespace Ui {
class PRTesterWidget;
}

class PRTesterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PRTesterWidget(QWidget *parent = 0);
    ~PRTesterWidget();

private slots:
    void on_btnStart_clicked();
    void on_btnBack_clicked();

private:
    Ui::PRTesterWidget *ui;
};

#endif // PRTESTERWIDGET_H
