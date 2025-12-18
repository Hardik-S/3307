#pragma once

#include <QObject>
#include <memory>
#include <vector>

#include "core/domain/Exercise.h"
#include "core/domain/Profile.h"
#include "core/domain/Result.h"

class IContentRepository;
class IProfileRepository;
class StrategyGrader;

class AppController : public QObject {
    Q_OBJECT

public:
    AppController(IContentRepository* contentRepository, IProfileRepository* profileRepository, QObject* parent = nullptr);

    void initialize();
    void startLesson();
    void submitAnswer(const QString& userAnswer);
    void advance();

    const Exercise* currentExercise() const;
    Profile& profile();

signals:
    void exerciseReady(const Exercise* exercise);
    void resultReady(const Result& result);
    void lessonFinished();
    void errorOccurred(const QString& message);

private:
    std::unique_ptr<StrategyGrader> createGraderFor(const Exercise* exercise) const;
    void loadExercises();
    void loadProfile();

    IContentRepository* m_contentRepository;
    IProfileRepository* m_profileRepository;
    std::vector<std::unique_ptr<Exercise>> m_exercises;
    int m_index;
    Profile m_profile;
};
