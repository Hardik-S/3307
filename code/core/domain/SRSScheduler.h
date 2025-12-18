#pragma once

#include <QDateTime>

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

class SRSScheduler {
public:
    QDateTime nextReview(const QDateTime& from, Difficulty difficulty) const;

#ifdef QT_DEBUG
    void advanceTimeTo(const QDateTime& futureTime);
    QDateTime now() const;
#endif

private:
#ifdef QT_DEBUG
    QDateTime m_simulatedTime;
    bool m_hasSimulated = false;
#endif
};
