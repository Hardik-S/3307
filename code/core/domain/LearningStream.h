#pragma once

#include <QString>
#include <vector>

#include "Unit.h"

class LearningStream {
public:
    LearningStream(const QString& id, const QString& name, const QString& language);

    const QString& id() const;
    const QString& name() const;
    const QString& language() const;

    void addUnit(Unit&& unit);
    const Unit* unitAt(int index) const;
    int unitCount() const;
    const std::vector<Unit>& units() const;

private:
    QString m_id;
    QString m_name;
    QString m_language;
    std::vector<Unit> m_units;
};
