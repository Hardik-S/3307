#pragma once

#include "IProfileRepository.h"

#include <QString>

class SQLiteProfileRepository : public IProfileRepository {
public:
    explicit SQLiteProfileRepository(const QString& dbPath = QString());
    Profile loadProfile(QString* error = nullptr) override;
    bool saveProfile(const Profile& profile, QString* error = nullptr) override;

private:
    bool ensureSchema(QString* error) const;
    QString resolveDbPath() const;

    QString m_dbPath;
};
