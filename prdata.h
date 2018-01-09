#ifndef PRDATA_H
#define PRDATA_H

#include <QString>
#include <QList>

class PRData
{
public:
    static PRData &instance();

    struct Entry {
        QString grandCycle;
        int gcNumber = -1;
        QString cycle;
        int cNumber = -1;
        QString title;
        int tNumber = -1;
    };

    QList<Entry> allEntries() const { return m_entries; }
    QStringList cycleNames() const;
    QStringList grandCycleNames() const;

    bool parseFile(const QString &path);
    bool parse(const QString &data);
    Entry randomEntry() const;
    Entry randomEntry(int &cur) const;

    Entry randomForCycle(int c) const;
    Entry randomForCycle(int c, int &cur) const;
    Entry randomForCycles(const QList<int> &c) const;
    Entry randomForCycles(const QList<int> &c, int &cur) const;
    Entry randomForGrandCycle(int gc) const;
    Entry randomForGrandCycle(int gc, int &cur) const;
    Entry randomForGrandCycles(const QList<int> &gc) const;
    Entry randomForGrandCycles(const QList<int> &gc, int &cur) const;

private:
    PRData();
    Q_DISABLE_COPY(PRData)

private:
    QList<Entry> m_entries;
    QList<int> m_gcBounds;
    QList<int> m_cBounds;

};

#endif // PRDATA_H
