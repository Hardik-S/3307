#pragma once

#include <QObject>
#include <memory>
#include <vector>

#include "core/domain/LearningStream.h"
#include "core/domain/Exercise.h"
#include "core/domain/Profile.h"
#include "core/domain/Result.h"

class IContentRepository;
class IProfileRepository;
class StrategyGrader;
class Exercise;
class Unit;

class AppController : public QObject {
    Q_OBJECT

public:
    AppController(IContentRepository* contentRepository, IProfileRepository* profileRepository, QObject* parent = nullptr);

    void initialize();
    bool startStream(const QString& streamId);
    void startUnit(const QString& streamId, const QString& unitId);
    void submitAnswer(const QString& userAnswer);
    void advance();
    void continueToNextUnit();

    const Exercise* currentExercise() const;
    const Unit* currentUnit() const;
    const std::vector<LearningStream>& streams() const;
    Profile& profile();

signals:
    void exerciseReady(const Exercise* exercise);
    void unitProgress(int current, int total);
    void resultReady(const Result& result);
    void unitCompleted(const QString& streamId, const QString& unitId, const QString& unitTitle);
    void streamFinished(const QString& streamId);
    void streamsReady();
    void errorOccurred(const QString& message);

private:
    std::unique_ptr<StrategyGrader> createGraderFor(const Exercise* exercise) const;
    void loadStreams();
    void loadProfile();
    bool setStreamById(const QString& streamId);
    bool setUnitById(const QString& unitId);

    IContentRepository* m_contentRepository;
    IProfileRepository* m_profileRepository;
    std::vector<LearningStream> m_streams;
    int m_streamIndex;
    int m_unitIndex;
    int m_exerciseIndex;
    Profile m_profile;
};
