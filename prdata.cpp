#include "prdata.h"
#include <QStringList>
#include <QDebug>
#include "randomsource.h"

PRData::PRData()
{
}

PRData &PRData::instance()
{
    static PRData inst_;
    return inst_;
}

QStringList PRData::cycleNames() const
{
    QStringList ret;
    for (int i = 0; i < m_cBounds.count() - 1; ++i) {
        ret << m_entries[m_cBounds[i]].cycle;
    }
    return ret;
}

QStringList PRData::grandCycleNames() const
{
    QStringList ret;
    for (int i = 0; i < m_gcBounds.count() - 1; ++i) {
        ret << m_entries[m_gcBounds[i]].grandCycle;
    }
    return ret;
}

bool PRData::parseFile(const QString &path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) return false;
    QTextStream ts(&f);
    ts.setCodec("UTF-8");
    QString data = ts.readAll();
    return parse(data);
}

bool PRData::parse(const QString &data)
{
    m_entries.clear();
    m_gcBounds.clear();
    m_cBounds.clear();

    QString curGC;
    QString curC;
    int nGC = 0;
    int nC = 0;
    int nT = 0;

    bool wasGC = false;
    bool wasC = false;

    QRegExp rxGC("\\{(.*)\\}");
    QRegExp rxC("\\[(.*)\\]");

    QStringList lines = data.split(QRegExp("\r|\n"), QString::SkipEmptyParts);
    for (QString l : qAsConst(lines))
    {
        if (rxGC.exactMatch(l)) {
            if (wasGC) {
                qWarning() << "Empty grand cycle";
                return false;
            }
            if (wasC) {
                qWarning() << "Empty cycle";
                return false;
            }
            curGC = rxGC.cap(1);
            nGC++;
            wasGC = true;
            wasC = false;
            m_gcBounds << nT;
        } else if (rxC.exactMatch(l)) {
            if (wasC) {
                qWarning() << "Empty cycle";
                return false;
            }
            curC = rxC.cap(1);
            nC++;
            wasGC = false;
            wasC = true;
            m_cBounds << nT;
        } else {
            if (curGC.isEmpty()) {
                qWarning() << "Need grand cycle before title";
                return false;
            }
            if (curC.isEmpty()) {
                qWarning() << "Need cycle before title";
                return false;
            }
            if (wasGC) {
                qWarning() << "Need cycle before title";
                return false;
            }
            m_entries << Entry { curGC, nGC, curC, nC, l, ++nT };
            wasGC = wasC = false;
        }
    }
    m_gcBounds << nT;
    m_cBounds << nT;
    return true;
}

PRData::Entry PRData::randomEntry() const
{
    int t = -1;
    return randomEntry(t);
}

PRData::Entry PRData::randomEntry(int &cur) const
{
    return m_entries.value(RandomSource::instance().nextRand(0, m_entries.count(), cur));
}

PRData::Entry PRData::randomForCycle(int c) const
{
    int t = -1;
    return randomForCycle(c, t);
}

PRData::Entry PRData::randomForCycle(int c, int &cur) const
{
    int s = m_cBounds.value(c);
    int e = m_cBounds.value(c+1);
    return m_entries.value(RandomSource::instance().nextRand(s, e, cur));
}

PRData::Entry PRData::randomForCycles(const QList<int> &c) const
{
    int t = -1;
    return randomForCycles(c, t);
}

PRData::Entry PRData::randomForCycles(const QList<int> &c, int &cur) const
{
    int idx = RandomSource::instance().nextRand(0, c.count());
    return randomForCycle(c[idx], cur);
}

PRData::Entry PRData::randomForGrandCycle(int gc) const
{
    int t = -1;
    return randomForGrandCycle(gc, t);
}

PRData::Entry PRData::randomForGrandCycle(int gc, int &cur) const
{
    int s = m_gcBounds.value(gc);
    int e = m_gcBounds.value(gc+1);
    return m_entries.value(RandomSource::instance().nextRand(s, e, cur));
}

PRData::Entry PRData::randomForGrandCycles(const QList<int> &gc) const
{
    int t = -1;
    return randomForGrandCycles(gc, t);
}

PRData::Entry PRData::randomForGrandCycles(const QList<int> &gc, int &cur) const
{
    int idx = RandomSource::instance().nextRand(0, gc.count());
    return randomForGrandCycle(gc[idx], cur);
}
