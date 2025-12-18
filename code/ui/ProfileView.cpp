#include "ProfileView.h"

#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>

#include "core/domain/Profile.h"

ProfileView::ProfileView(QWidget* parent)
    : QWidget(parent),
      m_profile(nullptr),
      m_nameLabel(new QLabel(this)),
      m_xpLabel(new QLabel(this)),
      m_streakLabel(new QLabel(this)),
      m_skillList(new QListWidget(this)) {
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(m_nameLabel);
    layout->addWidget(m_xpLabel);
    layout->addWidget(m_streakLabel);
    layout->addWidget(m_skillList);
    layout->addStretch(1);

    m_nameLabel->setStyleSheet("font-weight: bold; font-size: 18px;");
}

void ProfileView::attachProfile(Profile* profile) {
    if (m_profile) {
        m_profile->removeObserver(this);
    }
    m_profile = profile;
    if (m_profile) {
        m_profile->addObserver(this);
        refresh(*m_profile);
    }
}

void ProfileView::onProfileUpdated(const Profile& profile) {
    refresh(profile);
}

void ProfileView::refresh(const Profile& profile) {
    m_nameLabel->setText("Learner: " + profile.name());
    m_xpLabel->setText("XP: " + QString::number(profile.xp()));
    m_streakLabel->setText("Streak: " + QString::number(profile.streak()));
    m_skillList->clear();
    for (const auto& skill : profile.skills()) {
        m_skillList->addItem(skill.skillName() + " - Mastery " + QString::number(skill.mastery()) + "%");
    }
}
