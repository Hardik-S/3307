#include "PathView.h"

#include <QBrush>
#include <QColor>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>

#include "core/domain/LearningStream.h"
#include "core/domain/Profile.h"

namespace {
const char* kAdminPassword = "admin123";
}

PathView::PathView(QWidget* parent)
    : QWidget(parent),
      m_profile(nullptr),
      m_streams(nullptr),
      m_nepaliBox(new QGroupBox("Nepali Path", this)),
      m_kannadaBox(new QGroupBox("Kannada Path", this)),
      m_nepaliList(new QListWidget(this)),
      m_kannadaList(new QListWidget(this)) {
    auto* layout = new QVBoxLayout(this);
    auto* heading = new QLabel("Learning Path", this);
    heading->setStyleSheet("font-weight: bold; font-size: 18px;");

    auto* row = new QHBoxLayout();
    m_nepaliBox->setLayout(new QVBoxLayout());
    m_nepaliBox->layout()->addWidget(m_nepaliList);
    m_kannadaBox->setLayout(new QVBoxLayout());
    m_kannadaBox->layout()->addWidget(m_kannadaList);

    row->addWidget(m_nepaliBox, 1);
    row->addWidget(m_kannadaBox, 1);

    layout->addWidget(heading);
    layout->addLayout(row);

    connect(m_nepaliList, &QListWidget::itemDoubleClicked, this, &PathView::handleUnitActivated);
    connect(m_kannadaList, &QListWidget::itemDoubleClicked, this, &PathView::handleUnitActivated);
}

void PathView::setStreams(const std::vector<LearningStream>* streams) {
    m_streams = streams;
    rebuild();
}

void PathView::attachProfile(Profile* profile) {
    if (m_profile) {
        m_profile->removeObserver(this);
    }
    m_profile = profile;
    if (m_profile) {
        m_profile->addObserver(this);
    }
    rebuild();
}

void PathView::onProfileUpdated(const Profile&) {
    rebuild();
}

void PathView::rebuild() {
    m_nepaliList->clear();
    m_kannadaList->clear();
    if (!m_streams) {
        return;
    }
    for (const auto& stream : *m_streams) {
        if (stream.id() == "nepali") {
            renderStream(m_nepaliBox, m_nepaliList, stream);
        } else if (stream.id() == "kannada") {
            renderStream(m_kannadaBox, m_kannadaList, stream);
        }
    }
}

void PathView::renderStream(QGroupBox* box, QListWidget* list, const LearningStream& stream) {
    box->setTitle(stream.name());
    const auto& units = stream.units();
    for (size_t i = 0; i < units.size(); ++i) {
        const auto& unit = units[i];
        const bool completed = m_profile ? m_profile->isUnitCompleted(stream.id(), unit.id()) : false;
        const bool unlocked = isUnitUnlocked(stream, unit.id());
        QString status = completed ? "Completed" : (unlocked ? "Current" : "Locked");
        auto* item = new QListWidgetItem(QString("Unit %1: %2 — %3").arg(i + 1).arg(unit.title()).arg(status));
        item->setData(Qt::UserRole, stream.id());
        item->setData(Qt::UserRole + 1, unit.id());
        item->setData(Qt::UserRole + 2, unlocked || completed);
        if (completed) {
            item->setForeground(QBrush(QColor("#2e7d32")));
        } else if (!unlocked) {
            item->setForeground(QBrush(QColor("#999999")));
        }
        list->addItem(item);
    }
}

bool PathView::isUnitUnlocked(const LearningStream& stream, const QString& unitId) const {
    if (!m_profile) {
        return false;
    }
    const auto& units = stream.units();
    int lastCompletedIndex = -1;
    for (size_t i = 0; i < units.size(); ++i) {
        if (m_profile->isUnitCompleted(stream.id(), units[i].id())) {
            lastCompletedIndex = static_cast<int>(i);
        }
    }

    for (size_t i = 0; i < units.size(); ++i) {
        if (units[i].id() == unitId) {
            return static_cast<int>(i) <= lastCompletedIndex + 1;
        }
    }
    return false;
}

void PathView::handleUnitActivated(QListWidgetItem* item) {
    if (!item) {
        return;
    }
    const QString streamId = item->data(Qt::UserRole).toString();
    const QString unitId = item->data(Qt::UserRole + 1).toString();
    const bool unlocked = item->data(Qt::UserRole + 2).toBool();
    if (!unlocked) {
        bool ok = false;
        const QString password = QInputDialog::getText(this, "Admin Override", "Enter admin password:", QLineEdit::Password, QString(), &ok);
        if (!ok || password != kAdminPassword) {
            return;
        }
    }
    emit unitSelected(streamId, unitId);
}
