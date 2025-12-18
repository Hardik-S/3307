#pragma once

#include <QString>

class SkillProgress {
public:
    SkillProgress(const QString& skillName = QString());

    QString skillName() const;
    int mastery() const;
    int attempts() const;

    void recordAttempt(bool correct);
    void restore(int mastery, int attempts);

private:
    QString m_skillName;
    int m_mastery;
    int m_attempts;
};
