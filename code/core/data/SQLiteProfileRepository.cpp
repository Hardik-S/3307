#include "SQLiteProfileRepository.h"

#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>

#include "core/domain/Profile.h"

SQLiteProfileRepository::SQLiteProfileRepository(const QString& dbPath)
    : m_dbPath(dbPath) {}

QString SQLiteProfileRepository::resolveDbPath() const {
    if (!m_dbPath.isEmpty()) {
        return m_dbPath;
    }
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + "/bhashaquest.db";
}

bool SQLiteProfileRepository::ensureSchema(QString* error) const {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS profile (name TEXT, xp INTEGER, streak INTEGER)")) {
        if (error) {
            *error = query.lastError().text();
        }
        return false;
    }
    if (!query.exec("CREATE TABLE IF NOT EXISTS skill_progress (skill TEXT PRIMARY KEY, mastery INTEGER, attempts INTEGER)")) {
        if (error) {
            *error = query.lastError().text();
        }
        return false;
    }
    return true;
}

Profile SQLiteProfileRepository::loadProfile(QString* error) {
    const QString dbPath = resolveDbPath();
    const QString connectionName = "profile_connection_load";
    Profile profile;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName(dbPath);
        if (!db.open()) {
            if (error) {
                *error = db.lastError().text();
            }
            return Profile();
        }
        if (!ensureSchema(error)) {
            db.close();
            return Profile();
        }

        QSqlQuery query(db);
        if (query.exec("SELECT name, xp, streak FROM profile LIMIT 1")) {
            if (query.next()) {
                profile = Profile(query.value(0).toString());
                profile.restoreState(query.value(1).toInt(), query.value(2).toInt());
            }
        }

        if (query.exec("SELECT skill, mastery, attempts FROM skill_progress")) {
            while (query.next()) {
                profile.restoreSkill(query.value(0).toString(), query.value(1).toInt(), query.value(2).toInt());
            }
        }
        db.close();
    }
    QSqlDatabase::removeDatabase(connectionName);
    return profile;
}

bool SQLiteProfileRepository::saveProfile(const Profile& profile, QString* error) {
    const QString dbPath = resolveDbPath();
    const QString connectionName = "profile_connection_save";
    bool ok = true;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName(dbPath);
        if (!db.open()) {
            if (error) {
                *error = db.lastError().text();
            }
            return false;
        }
        if (!ensureSchema(error)) {
            db.close();
            return false;
        }

        QSqlQuery query(db);
        query.exec("DELETE FROM profile");
        query.prepare("INSERT INTO profile (name, xp, streak) VALUES (?, ?, ?)");
        query.addBindValue(profile.name());
        query.addBindValue(profile.xp());
        query.addBindValue(profile.streak());
        if (!query.exec()) {
            if (error) {
                *error = query.lastError().text();
            }
            ok = false;
        }

        if (ok) {
            query.exec("DELETE FROM skill_progress");
            query.prepare("INSERT INTO skill_progress (skill, mastery, attempts) VALUES (?, ?, ?)");
            for (const auto& skill : profile.skills()) {
                query.addBindValue(skill.skillName());
                query.addBindValue(skill.mastery());
                query.addBindValue(skill.attempts());
                if (!query.exec()) {
                    if (error) {
                        *error = query.lastError().text();
                    }
                    ok = false;
                    break;
                }
                query.finish();
            }
        }

        db.close();
    }
    QSqlDatabase::removeDatabase(connectionName);
    return ok;
}
