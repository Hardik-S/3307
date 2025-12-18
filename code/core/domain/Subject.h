#pragma once

#include <QVector>

#include "Observer.h"

class Profile;

class Subject {
public:
    void addObserver(ProfileObserver* observer);
    void removeObserver(ProfileObserver* observer);

protected:
    void notifyProfileUpdated(const Profile& profile);

private:
    QVector<ProfileObserver*> m_observers;
};
