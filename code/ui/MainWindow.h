#pragma once

#include <QMainWindow>

class QTabWidget;
class HomeView;
class LessonView;
class PathView;
class ProfileView;
class UnitCompleteDialog;

class AppController;
class Exercise;
struct Result;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(AppController* controller, QWidget* parent = nullptr);

private slots:
    void handleResult(const Result& result);
    void handleExerciseReady(const Exercise* exercise);
    void handleUnitCompleted(const QString& streamId, const QString& unitId, const QString& unitTitle);
    void handleStreamFinished(const QString& streamId);
    void handleError(const QString& message);
    void playAudio();
    void handleUnitProgress(int current, int total);

private:
    AppController* m_controller;
    QTabWidget* m_tabs;
    HomeView* m_homeView;
    LessonView* m_lessonView;
    PathView* m_pathView;
    ProfileView* m_profileView;
};
