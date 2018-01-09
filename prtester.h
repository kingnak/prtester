#ifndef PRTESTER_H
#define PRTESTER_H

#include <QList>

class PRTester
{
public:
    PRTester();

    PRTester &byAll();
    PRTester &byGrandCycles(QList<int> gc);
    PRTester &byCycles(QList<int> c);
    PRTester &askAll();
    PRTester &askNumber();
    PRTester &askTitle();

    class Question {
    public:
        Question() {}
        Question(const QString &q, const QString &a) : m_question(q), m_answer(a) {}
        QString question() const { return m_question; }
        QString answer() const { return m_answer; }
        bool verify(const QString &answer) const;
    private:
        QString m_question;
        QString m_answer;
    };

    Question nextQuestion();

private:
    bool m_byGrandCycle = false;
    bool m_byCycle = false;
    QList<int> m_grandCycles;
    QList<int> m_cycles;

    enum AskType {
        AskNone = 0x0000,
        AskNumber = 0x0001,
        AskTitle = 0x0002,

        AskAll = AskNumber | AskTitle
    };
    Q_DECLARE_FLAGS(AskTypes, AskType)
    AskTypes m_askTypes = AskNone;
    int m_lastIdx = -1;
};

#endif // PRTESTER_H
