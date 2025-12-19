#include "AppController.h"

#include "core/data/IContentRepository.h"
#include "core/data/IProfileRepository.h"
#include "core/domain/AudioManager.h"
#include "core/domain/CharacterSelectionGrader.h"
#include "core/domain/ListenGrader.h"
#include "core/domain/MCQGrader.h"
#include "core/domain/Profile.h"
#include "core/domain/SRSScheduler.h"
#include "core/domain/SpeakGrader.h"
#include "core/domain/StrategyGrader.h"
#include "core/domain/TileOrderGrader.h"
#include "core/domain/TranslateGrader.h"
#include "core/domain/TranslateExercise.h"

AppController::AppController(IContentRepository* contentRepository, IProfileRepository* profileRepository, QObject* parent)
    : QObject(parent),
      m_contentRepository(contentRepository),
      m_profileRepository(profileRepository),
      m_streamIndex(-1),
      m_unitIndex(-1),
      m_exerciseIndex(-1) {}

void AppController::initialize() {
    loadProfile();
    loadStreams();
}

void AppController::loadProfile() {
    if (!m_profileRepository) {
        m_profile = Profile();
        return;
    }
    QString error;
    m_profile = m_profileRepository->loadProfile(&error);
    if (!error.isEmpty()) {
        emit errorOccurred(error);
    }
}

void AppController::loadStreams() {
    m_streams.clear();
    if (!m_contentRepository) {
        emit errorOccurred("No content repository configured.");
        return;
    }
    QString error;
    m_streams = m_contentRepository->loadStreams(&error);
    if (!error.isEmpty()) {
        emit errorOccurred(error);
    }
    emit streamsReady();
}

bool AppController::startStream(const QString& streamId) {
    if (!setStreamById(streamId)) {
        emit errorOccurred("Stream not found.");
        return false;
    }
    m_unitIndex = 0;
    m_exerciseIndex = 0;
    const Unit* unit = currentUnit();
    if (!unit || unit->size() == 0) {
        emit errorOccurred("Unit is empty.");
        return false;
    }
    emit exerciseReady(unit->exerciseAt(m_exerciseIndex));
    emit unitProgress(m_exerciseIndex + 1, unit->size());
    return true;
}

void AppController::startUnit(const QString& streamId, const QString& unitId) {
    if (!setStreamById(streamId) || !setUnitById(unitId)) {
        emit errorOccurred("Unit not found.");
        return;
    }
    m_exerciseIndex = 0;
    const Unit* unit = currentUnit();
    if (!unit || unit->size() == 0) {
        emit errorOccurred("Unit is empty.");
        return;
    }
    emit exerciseReady(unit->exerciseAt(m_exerciseIndex));
    emit unitProgress(m_exerciseIndex + 1, unit->size());
}

void AppController::submitAnswer(const QString& userAnswer) {
    const Unit* unit = currentUnit();
    if (!unit || m_exerciseIndex < 0 || m_exerciseIndex >= unit->size()) {
        emit errorOccurred("No active exercise.");
        return;
    }
    const Exercise* exercise = unit->exerciseAt(m_exerciseIndex);
    auto grader = createGraderFor(exercise);
    if (!grader) {
        emit errorOccurred("No grader available for exercise.");
        return;
    }

    const Result result = grader->grade(userAnswer, exercise);
    if (result.correct) {
        AudioManager::instance().playSuccess();
    } else {
        AudioManager::instance().playError();
    }

    m_profile.addXp(result.score);
    m_profile.updateStreak(result.correct);
    m_profile.recordSkillAttempt(exercise->type(), result.correct);

    if (m_profileRepository) {
        QString error;
        m_profileRepository->saveProfile(m_profile, &error);
        if (!error.isEmpty()) {
            emit errorOccurred(error);
        }
    }

    emit resultReady(result);
}

void AppController::advance() {
    const Unit* unit = currentUnit();
    if (!unit) {
        return;
    }
    m_exerciseIndex++;
    if (m_exerciseIndex >= unit->size()) {
        m_profile.markUnitCompleted(m_streams[m_streamIndex].id(), unit->id());
        if (m_profileRepository) {
            QString error;
            m_profileRepository->saveProfile(m_profile, &error);
            if (!error.isEmpty()) {
                emit errorOccurred(error);
            }
        }
        emit unitCompleted(m_streams[m_streamIndex].id(), unit->id(), unit->title());
        return;
    }
    emit exerciseReady(unit->exerciseAt(m_exerciseIndex));
    emit unitProgress(m_exerciseIndex + 1, unit->size());
}

void AppController::continueToNextUnit() {
    const auto* stream = (m_streamIndex >= 0 && m_streamIndex < static_cast<int>(m_streams.size()))
        ? &m_streams[static_cast<size_t>(m_streamIndex)]
        : nullptr;
    if (!stream) {
        return;
    }
    m_unitIndex++;
    if (m_unitIndex >= stream->unitCount()) {
        emit streamFinished(stream->id());
        return;
    }
    m_exerciseIndex = 0;
    const Unit* unit = currentUnit();
    if (!unit || unit->size() == 0) {
        emit errorOccurred("Unit is empty.");
        return;
    }
    emit exerciseReady(unit->exerciseAt(m_exerciseIndex));
    emit unitProgress(m_exerciseIndex + 1, unit->size());
}

const Exercise* AppController::currentExercise() const {
    const Unit* unit = currentUnit();
    if (!unit) {
        return nullptr;
    }
    return unit->exerciseAt(m_exerciseIndex);
}

const Unit* AppController::currentUnit() const {
    const auto* stream = (m_streamIndex >= 0 && m_streamIndex < static_cast<int>(m_streams.size()))
        ? &m_streams[static_cast<size_t>(m_streamIndex)]
        : nullptr;
    if (!stream) {
        return nullptr;
    }
    return stream->unitAt(m_unitIndex);
}

const std::vector<LearningStream>& AppController::streams() const {
    return m_streams;
}

Profile& AppController::profile() {
    return m_profile;
}

std::unique_ptr<StrategyGrader> AppController::createGraderFor(const Exercise* exercise) const {
    if (!exercise) {
        return nullptr;
    }
    if (exercise->type() == "MCQ") {
        return std::make_unique<MCQGrader>();
    }
    if (exercise->type() == "Translate") {
        const auto* translate = dynamic_cast<const TranslateExercise*>(exercise);
        if (translate && translate->usesCharacterSelection()) {
            return std::make_unique<CharacterSelectionGrader>();
        }
        return std::make_unique<TranslateGrader>();
    }
    if (exercise->type() == "TileOrder") {
        return std::make_unique<TileOrderGrader>();
    }
    if (exercise->type() == "Listen") {
        return std::make_unique<ListenGrader>();
    }
    if (exercise->type() == "Speak") {
        return std::make_unique<SpeakGrader>();
    }
    return nullptr;
}

bool AppController::setStreamById(const QString& streamId) {
    for (size_t i = 0; i < m_streams.size(); ++i) {
        if (m_streams[i].id() == streamId) {
            m_streamIndex = static_cast<int>(i);
            return true;
        }
    }
    return false;
}

bool AppController::setUnitById(const QString& unitId) {
    if (m_streamIndex < 0 || m_streamIndex >= static_cast<int>(m_streams.size())) {
        return false;
    }
    const auto& units = m_streams[static_cast<size_t>(m_streamIndex)].units();
    for (size_t i = 0; i < units.size(); ++i) {
        if (units[i].id() == unitId) {
            m_unitIndex = static_cast<int>(i);
            return true;
        }
    }
    return false;
}
