#pragma once

#include <QWidget>

#include <QDate>

#include "core/domain/Observer.h"

class QLabel;
class QListWidget;
class Profile;
class QPushButton;

class ProfileView : public QWidget, public ProfileObserver {
    Q_OBJECT

public:
    explicit ProfileView(QWidget* parent = nullptr);

    void attachProfile(Profile* profile);
    void onProfileUpdated(const Profile& profile) override;

private slots:
    void handleAdvanceDay();

private:
    void refresh(const Profile& profile);

    Profile* m_profile;
    QLabel* m_nameLabel;
    QLabel* m_xpLabel;
    QLabel* m_streakLabel;
    QLabel* m_dateLabel;
    QListWidget* m_skillList;
    QPushButton* m_advanceDayButton;
    QDate m_currentDate;
};
