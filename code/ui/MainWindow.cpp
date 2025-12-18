#include "MainWindow.h"

#include <QMessageBox>
#include <QStackedWidget>
#include <QToolBar>

#include "core/controllers/AppController.h"
#include "core/domain/AudioManager.h"
#include "core/domain/Exercise.h"
#include "core/domain/Result.h"
#include "ui/HomeView.h"
#include "ui/LessonView.h"
#include "ui/ProfileView.h"

MainWindow::MainWindow(AppController* controller, QWidget* parent)
    : QMainWindow(parent),
      m_controller(controller),
      m_stack(new QStackedWidget(this)),
      m_homeView(new HomeView(this)),
      m_lessonView(new LessonView(this)),
      m_profileView(new ProfileView(this)) {
    setWindowTitle("Bhasha Quest");
    setMinimumSize(800, 600);

    auto* toolbar = addToolBar("Navigation");
    toolbar->addAction("Home", this, &MainWindow::showHome);
    toolbar->addAction("Lesson", this, &MainWindow::showLesson);
    toolbar->addAction("Profile", this, &MainWindow::showProfile);

    m_stack->addWidget(m_homeView);
    m_stack->addWidget(m_lessonView);
    m_stack->addWidget(m_profileView);
    setCentralWidget(m_stack);

    connect(m_homeView, &HomeView::startLessonRequested, m_controller, &AppController::startLesson);
    connect(m_homeView, &HomeView::profileRequested, this, &MainWindow::showProfile);
    connect(m_lessonView, &LessonView::answerSubmitted, m_controller, &AppController::submitAnswer);
    connect(m_lessonView, &LessonView::nextRequested, m_controller, &AppController::advance);
    connect(m_lessonView, &LessonView::playAudioRequested, this, &MainWindow::playAudio);

    connect(m_controller, &AppController::exerciseReady, this, &MainWindow::handleExerciseReady);
    connect(m_controller, &AppController::resultReady, this, &MainWindow::handleResult);
    connect(m_controller, &AppController::lessonFinished, this, &MainWindow::handleLessonFinished);
    connect(m_controller, &AppController::errorOccurred, this, &MainWindow::handleError);

    if (m_controller) {
        m_profileView->attachProfile(&m_controller->profile());
    }

    showHome();
}

void MainWindow::showHome() {
    m_stack->setCurrentWidget(m_homeView);
}

void MainWindow::showLesson() {
    m_stack->setCurrentWidget(m_lessonView);
}

void MainWindow::showProfile() {
    m_stack->setCurrentWidget(m_profileView);
}

void MainWindow::handleResult(const Result& result) {
    m_lessonView->showResult(result.feedback + " (Score: " + QString::number(result.score) + ")");
}

void MainWindow::handleExerciseReady(const Exercise* exercise) {
    m_lessonView->setExercise(exercise);
    showLesson();
}

void MainWindow::handleLessonFinished() {
    QMessageBox::information(this, "Lesson", "Lesson complete!");
    showHome();
}

void MainWindow::handleError(const QString& message) {
    QMessageBox::warning(this, "Error", message);
}

void MainWindow::playAudio() {
    const auto* exercise = m_controller ? m_controller->currentExercise() : nullptr;
    if (!exercise) {
        return;
    }
    AudioManager::instance().playAudio(exercise->audioPath());
}
