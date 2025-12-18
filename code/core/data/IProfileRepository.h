#pragma once

#include <QString>

class Profile;

class IProfileRepository {
public:
    virtual ~IProfileRepository() = default;
    virtual Profile loadProfile(QString* error = nullptr) = 0;
    virtual bool saveProfile(const Profile& profile, QString* error = nullptr) = 0;
};
