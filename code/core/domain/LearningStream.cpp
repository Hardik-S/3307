#include "LearningStream.h"

LearningStream::LearningStream(const QString& id, const QString& name, const QString& language)
    : m_id(id), m_name(name), m_language(language) {}

const QString& LearningStream::id() const {
    return m_id;
}

const QString& LearningStream::name() const {
    return m_name;
}

const QString& LearningStream::language() const {
    return m_language;
}

void LearningStream::addUnit(Unit&& unit) {
    m_units.emplace_back(std::move(unit));
}

const Unit* LearningStream::unitAt(int index) const {
    if (index < 0 || index >= static_cast<int>(m_units.size())) {
        return nullptr;
    }
    return &m_units[static_cast<size_t>(index)];
}

int LearningStream::unitCount() const {
    return static_cast<int>(m_units.size());
}

const std::vector<Unit>& LearningStream::units() const {
    return m_units;
}
