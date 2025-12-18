#pragma once

#include <QMap>
#include <QString>

#include "SkillProgress.h"
#include "Subject.h"

class Profile : public Subject {
public:
    explicit Profile(const QString& name = "Learner");

    QString name() const;
    int xp() const;
    int streak() const;

    void addXp(int amount);
    void updateStreak(bool correct);
    void recordSkillAttempt(const QString& skillName, bool correct);
    void restoreState(int xp, int streak);
    void restoreSkill(const QString& skillName, int mastery, int attempts);

    const QMap<QString, SkillProgress>& skills() const;

private:
    QString m_name;
    int m_xp;
    int m_streak;
    QMap<QString, SkillProgress> m_skills;
};
