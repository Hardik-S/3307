#include "SkillProgress.h"

#include <QtGlobal>

SkillProgress::SkillProgress(const QString& skillName)
    : m_skillName(skillName), m_mastery(0), m_attempts(0) {}

QString SkillProgress::skillName() const {
    return m_skillName;
}

int SkillProgress::mastery() const {
    return m_mastery;
}

int SkillProgress::attempts() const {
    return m_attempts;
}

void SkillProgress::recordAttempt(bool correct) {
    m_attempts++;
    if (correct) {
        m_mastery = qMin(100, m_mastery + 10);
    } else {
        m_mastery = qMax(0, m_mastery - 5);
    }
}

void SkillProgress::restore(int mastery, int attempts) {
    m_mastery = mastery;
    m_attempts = attempts;
}
