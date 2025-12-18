#pragma once

#include <QMainWindow>

class QStackedWidget;
class HomeView;
class LessonView;
class ProfileView;

class AppController;
class Exercise;
struct Result;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(AppController* controller, QWidget* parent = nullptr);

private slots:
    void showHome();
    void showLesson();
    void showProfile();
    void handleResult(const Result& result);
    void handleExerciseReady(const Exercise* exercise);
    void handleLessonFinished();
    void handleError(const QString& message);
    void playAudio();

private:
    AppController* m_controller;
    QStackedWidget* m_stack;
    HomeView* m_homeView;
    LessonView* m_lessonView;
    ProfileView* m_profileView;
};
