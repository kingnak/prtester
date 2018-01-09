#include "prtester.h"
#include "prdata.h"
#include "randomsource.h"

PRTester::PRTester()
{

}

PRTester &PRTester::byAll()
{
    m_byCycle = m_byGrandCycle = false;
    return *this;
}

PRTester &PRTester::byGrandCycles(QList<int> gc)
{
    m_byCycle = false;
    m_byGrandCycle = true;
    m_grandCycles = gc;
    return *this;
}

PRTester &PRTester::byCycles(QList<int> c)
{
    m_byGrandCycle = false;
    m_byCycle = true;
    m_cycles = c;
    return *this;
}

PRTester &PRTester::askAll()
{
    m_askTypes = AskAll;
    return *this;
}


PRTester &PRTester::askNumber()
{
    m_askTypes |= AskNumber;
    return *this;
}


PRTester &PRTester::askTitle()
{
    m_askTypes |= AskTitle;
    return *this;
}

PRTester::Question PRTester::nextQuestion()
{
    PRData::Entry e;
    if (m_byGrandCycle)
        e = PRData::instance().randomForGrandCycles(m_grandCycles, m_lastIdx);
    else if (m_byCycle)
        e = PRData::instance().randomForCycles(m_cycles, m_lastIdx);
    else
        e = PRData::instance().randomEntry(m_lastIdx);

    QList<AskType> types;
    if (m_askTypes.testFlag(AskNumber)) types << AskNumber;
    if (m_askTypes.testFlag(AskTitle)) types << AskTitle;

    int idx = RandomSource::instance().nextRand(0, types.count());
    if (types[idx] == AskNumber)
        return Question(QString::number(e.tNumber), e.title);
    else
        return Question(e.title, QString::number(e.tNumber));
}

bool PRTester::Question::verify(const QString &answer) const
{
    auto f = [](QString s)->QString{
        s = s.toLower();
        s = s.replace(QRegExp("\\s+"), " ");
        s = s.remove(QRegExp("^(der|die|das)\\b"));
        s = s.trimmed();
        return s;
    };

    return f(answer) == f(m_answer);
}
