#include "Subject.h"

#include "Profile.h"

void Subject::addObserver(ProfileObserver* observer) {
    if (!observer || m_observers.contains(observer)) {
        return;
    }
    m_observers.append(observer);
}

void Subject::removeObserver(ProfileObserver* observer) {
    m_observers.removeAll(observer);
}

void Subject::notifyProfileUpdated(const Profile& profile) {
    for (auto* observer : m_observers) {
        if (observer) {
            observer->onProfileUpdated(profile);
        }
    }
}
