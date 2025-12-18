#pragma once

#include "IProfileRepository.h"

#include <QString>

class JsonProfileRepository : public IProfileRepository {
public:
    explicit JsonProfileRepository(const QString& profilePath = QString());
    Profile loadProfile(QString* error = nullptr) override;
    bool saveProfile(const Profile& profile, QString* error = nullptr) override;

private:
    QString resolveProfilePath() const;
    QString m_profilePath;
};
