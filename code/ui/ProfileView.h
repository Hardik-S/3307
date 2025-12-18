#pragma once

#include <QWidget>

#include "core/domain/Observer.h"

class QLabel;
class QListWidget;
class Profile;

class ProfileView : public QWidget, public ProfileObserver {
    Q_OBJECT

public:
    explicit ProfileView(QWidget* parent = nullptr);

    void attachProfile(Profile* profile);
    void onProfileUpdated(const Profile& profile) override;

private:
    void refresh(const Profile& profile);

    Profile* m_profile;
    QLabel* m_nameLabel;
    QLabel* m_xpLabel;
    QLabel* m_streakLabel;
    QListWidget* m_skillList;
};
