#include "SRSScheduler.h"

QDateTime SRSScheduler::nextReview(const QDateTime& from, Difficulty difficulty) const {
    switch (difficulty) {
        case Difficulty::Easy:
            return from.addDays(2);
        case Difficulty::Medium:
            return from.addDays(1);
        case Difficulty::Hard:
        default:
            return from.addSecs(6 * 60 * 60);
    }
}

#ifdef QT_DEBUG
void SRSScheduler::advanceTimeTo(const QDateTime& futureTime) {
    m_simulatedTime = futureTime;
    m_hasSimulated = true;
}

QDateTime SRSScheduler::now() const {
    return m_hasSimulated ? m_simulatedTime : QDateTime::currentDateTime();
}
#endif
