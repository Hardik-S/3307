#pragma once

#include <QMap>
#include <QSet>
#include <QString>

#include "SkillProgress.h"
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
    void markUnitCompleted(const QString& streamId, const QString& unitId);
    bool isUnitCompleted(const QString& streamId, const QString& unitId) const;
    QSet<QString> completedUnits(const QString& streamId) const;
    const QMap<QString, QSet<QString>>& completedUnitMap() const;

    const QMap<QString, SkillProgress>& skills() const;

private:
    QString m_name;
    int m_xp;
    int m_streak;
    QMap<QString, SkillProgress> m_skills;
    QMap<QString, QSet<QString>> m_completedUnits;
};
