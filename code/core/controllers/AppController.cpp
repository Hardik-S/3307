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
      m_index(-1) {}

void AppController::initialize() {
    loadProfile();
    loadExercises();
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

void AppController::loadExercises() {
    m_exercises.clear();
    if (!m_contentRepository) {
        emit errorOccurred("No content repository configured.");
        return;
    }
    QString error;
    const auto exercises = m_contentRepository->loadExercises(&error);
    for (auto* exercise : exercises) {
        m_exercises.emplace_back(exercise);
    }
    if (!error.isEmpty()) {
        emit errorOccurred(error);
    }
}

void AppController::startLesson() {
    if (m_exercises.empty()) {
        emit errorOccurred("No exercises available.");
        return;
    }
    m_index = 0;
    emit exerciseReady(m_exercises[m_index].get());
}

void AppController::submitAnswer(const QString& userAnswer) {
    if (m_index < 0 || m_index >= static_cast<int>(m_exercises.size())) {
        emit errorOccurred("No active exercise.");
        return;
    }
    const Exercise* exercise = m_exercises[m_index].get();
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
    if (m_index < 0) {
        return;
    }
    m_index++;
    if (m_index >= static_cast<int>(m_exercises.size())) {
        emit lessonFinished();
        return;
    }
    emit exerciseReady(m_exercises[m_index].get());
}

const Exercise* AppController::currentExercise() const {
    if (m_index < 0 || m_index >= static_cast<int>(m_exercises.size())) {
        return nullptr;
    }
    return m_exercises[m_index].get();
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
