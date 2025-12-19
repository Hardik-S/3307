#include "JsonProfileRepository.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "core/domain/Profile.h"

JsonProfileRepository::JsonProfileRepository(const QString& profilePath)
    : m_profilePath(profilePath) {}

QString JsonProfileRepository::resolveProfilePath() const {
    if (!m_profilePath.isEmpty()) {
        return m_profilePath;
    }
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + "/profile.json";
}

Profile JsonProfileRepository::loadProfile(QString* error) {
    const QString path = resolveProfilePath();
    QFile file(path);
    if (!file.exists()) {
        return Profile();
    }
    if (!file.open(QIODevice::ReadOnly)) {
        if (error) {
            *error = "Failed to open profile.json.";
        }
        return Profile();
    }

    const auto doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) {
        if (error) {
            *error = "Profile JSON root is not an object.";
        }
        return Profile();
    }

    const auto obj = doc.object();
    Profile profile(obj.value("name").toString("Learner"));
    profile.restoreState(obj.value("xp").toInt(), obj.value("streak").toInt());

    const auto skills = obj.value("skills").toArray();
    for (const auto& skillValue : skills) {
        const auto skillObj = skillValue.toObject();
        const QString skillName = skillObj.value("name").toString();
        const int mastery = skillObj.value("mastery").toInt();
        const int attempts = skillObj.value("attempts").toInt();
        profile.restoreSkill(skillName, mastery, attempts);
    }

    const auto completedUnitsObj = obj.value("completedUnits").toObject();
    for (auto it = completedUnitsObj.begin(); it != completedUnitsObj.end(); ++it) {
        const QString streamId = it.key();
        const auto unitArray = it.value().toArray();
        for (const auto& unitValue : unitArray) {
            profile.markUnitCompleted(streamId, unitValue.toString());
        }
    }

    return profile;
}

bool JsonProfileRepository::saveProfile(const Profile& profile, QString* error) {
    const QString path = resolveProfilePath();
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        if (error) {
            *error = "Failed to write profile.json.";
        }
        return false;
    }

    QJsonObject obj;
    obj.insert("name", profile.name());
    obj.insert("xp", profile.xp());
    obj.insert("streak", profile.streak());

    QJsonArray skills;
    for (const auto& skill : profile.skills()) {
        QJsonObject skillObj;
        skillObj.insert("name", skill.skillName());
        skillObj.insert("mastery", skill.mastery());
        skillObj.insert("attempts", skill.attempts());
        skills.append(skillObj);
    }
    obj.insert("skills", skills);

    QJsonObject completedUnits;
    for (auto it = profile.completedUnitMap().begin(); it != profile.completedUnitMap().end(); ++it) {
        QJsonArray unitArray;
        for (const auto& unitId : it.value()) {
            unitArray.append(unitId);
        }
        completedUnits.insert(it.key(), unitArray);
    }
    obj.insert("completedUnits", completedUnits);

    QJsonDocument doc(obj);
    file.write(doc.toJson());
    return true;
}
