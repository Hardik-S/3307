#pragma once

#include <QWidget>

#include <vector>

#include "core/domain/Observer.h"

class QListWidget;
class QListWidgetItem;
class QGroupBox;
class Profile;
class LearningStream;

class PathView : public QWidget, public ProfileObserver {
    Q_OBJECT

public:
    explicit PathView(QWidget* parent = nullptr);

    void setStreams(const std::vector<LearningStream>* streams);
    void attachProfile(Profile* profile);
    void onProfileUpdated(const Profile& profile) override;

signals:
    void unitSelected(const QString& streamId, const QString& unitId);

private slots:
    void handleUnitActivated(QListWidgetItem* item);

private:
    void rebuild();
    void renderStream(QGroupBox* box, QListWidget* list, const LearningStream& stream);
    bool isUnitUnlocked(const LearningStream& stream, const QString& unitId) const;

    Profile* m_profile;
    const std::vector<LearningStream>* m_streams;
    QGroupBox* m_nepaliBox;
    QGroupBox* m_kannadaBox;
    QListWidget* m_nepaliList;
    QListWidget* m_kannadaList;
};
