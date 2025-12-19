#include "ProfileView.h"

#include <QDate>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "core/domain/Profile.h"

ProfileView::ProfileView(QWidget* parent)
    : QWidget(parent),
      m_profile(nullptr),
      m_nameLabel(new QLabel(this)),
      m_xpLabel(new QLabel(this)),
      m_streakLabel(new QLabel(this)),
      m_dateLabel(new QLabel(this)),
      m_skillList(new QListWidget(this)),
      m_advanceDayButton(new QPushButton("+1 Day", this)),
      m_currentDate(QDate::currentDate()) {
    setStyleSheet(
        "QWidget {"
        "    background-color: #f5f5f5;"
        "}"
        "QLabel {"
        "    color: #333333;"
        "}"
        "QFrame {"
        "    background-color: white;"
        "    border-radius: 10px;"
        "}"
        "QListWidget {"
        "    background-color: white;"
        "    border: 2px solid #e0e0e0;"
        "    border-radius: 10px;"
        "    padding: 10px;"
        "}"
        "QListWidget::item {"
        "    background-color: #f9f9f9;"
        "    border: 1px solid #e0e0e0;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "    margin: 3px;"
        "}"
        "QProgressBar {"
        "    border: 2px solid #e0e0e0;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "    height: 25px;"
        "    background-color: #f0f0f0;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #4CAF50;"
        "    border-radius: 3px;"
        "}"
    );
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(m_nameLabel);
    layout->addWidget(m_xpLabel);
    layout->addWidget(m_streakLabel);
    layout->addWidget(m_dateLabel);
    layout->addWidget(m_advanceDayButton);
    layout->addWidget(m_skillList);
    layout->addStretch(1);

    m_nameLabel->setStyleSheet("font-weight: bold; font-size: 18px;");

    connect(m_advanceDayButton, &QPushButton::clicked, this, &ProfileView::handleAdvanceDay);
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
    m_dateLabel->setText("Current Date: " + m_currentDate.toString("yyyy-MM-dd"));
    m_skillList->clear();
    for (const auto& skill : profile.skills()) {
        m_skillList->addItem(skill.skillName() + " - Mastery " + QString::number(skill.mastery()) + "%");
    }
}

void ProfileView::handleAdvanceDay() {
    m_currentDate = m_currentDate.addDays(1);
    if (m_profile) {
        m_profile->updateStreak(true);
        refresh(*m_profile);
    } else {
        m_dateLabel->setText("Current Date: " + m_currentDate.toString("yyyy-MM-dd"));
    }
}
