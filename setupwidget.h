#ifndef SETUPWIDGET_H
#define SETUPWIDGET_H

#include <QWidget>

class PRTester;
class QListWidget;

namespace Ui {
class SetupWidget;
}

class SetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetupWidget(QWidget *parent = 0);
    ~SetupWidget();

    PRTester getTester();

signals:
    void canStart(bool);

private slots:
    void checkCanStart();

private:
    void setupList(QListWidget *lst, const QStringList &items);
    QList<int> checkedItems(QListWidget *lst);

private:
    Ui::SetupWidget *ui;
};

#endif // SETUPWIDGET_H
