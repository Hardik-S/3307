#include "Profile.h"

Profile::Profile(const QString& name)
    : m_name(name), m_xp(0), m_streak(0) {}

QString Profile::name() const {
    return m_name;
}

int Profile::xp() const {
    return m_xp;
}

int Profile::streak() const {
    return m_streak;
}

void Profile::addXp(int amount) {
    m_xp += amount;
    notifyProfileUpdated(*this);
}

void Profile::updateStreak(bool correct) {
    if (correct) {
        m_streak++;
    } else {
        m_streak = 0;
    }
    notifyProfileUpdated(*this);
}

void Profile::recordSkillAttempt(const QString& skillName, bool correct) {
    if (!m_skills.contains(skillName)) {
        m_skills.insert(skillName, SkillProgress(skillName));
    }
    m_skills[skillName].recordAttempt(correct);
    notifyProfileUpdated(*this);
}

void Profile::restoreState(int xp, int streak) {
    m_xp = xp;
    m_streak = streak;
}

void Profile::restoreSkill(const QString& skillName, int mastery, int attempts) {
    if (!m_skills.contains(skillName)) {
        m_skills.insert(skillName, SkillProgress(skillName));
    }
    m_skills[skillName].restore(mastery, attempts);
}

const QMap<QString, SkillProgress>& Profile::skills() const {
    return m_skills;
}
