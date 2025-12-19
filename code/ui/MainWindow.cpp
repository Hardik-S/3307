#include "MainWindow.h"

#include <QMessageBox>
#include <QTabWidget>

#include "core/controllers/AppController.h"
#include "core/domain/AudioManager.h"
#include "core/domain/Exercise.h"
#include "core/domain/Result.h"
#include "ui/HomeView.h"
#include "ui/LessonView.h"
#include "ui/PathView.h"
#include "ui/ProfileView.h"
#include "ui/UnitCompleteDialog.h"

MainWindow::MainWindow(AppController* controller, QWidget* parent)
    : QMainWindow(parent),
      m_controller(controller),
      m_tabs(new QTabWidget(this)),
      m_homeView(new HomeView(this)),
      m_lessonView(new LessonView(this)),
      m_pathView(new PathView(this)),
      m_profileView(new ProfileView(this)) {
    setWindowTitle("Bhasha Quest");
    setMinimumSize(900, 640);

    m_tabs->addTab(m_homeView, "Home");
    m_tabs->addTab(m_lessonView, "Lesson");
    m_tabs->addTab(m_pathView, "Path");
    m_tabs->addTab(m_profileView, "Profile");
    setCentralWidget(m_tabs);

    connect(m_homeView, &HomeView::startStreamRequested, m_controller, &AppController::startStream);
    connect(m_homeView, &HomeView::profileRequested, [this]() { m_tabs->setCurrentWidget(m_profileView); });
    connect(m_lessonView, &LessonView::answerSubmitted, m_controller, &AppController::submitAnswer);
    connect(m_lessonView, &LessonView::nextRequested, m_controller, &AppController::advance);
    connect(m_lessonView, &LessonView::playAudioRequested, this, &MainWindow::playAudio);
    connect(m_pathView, &PathView::unitSelected, m_controller, &AppController::startUnit);

    connect(m_controller, &AppController::exerciseReady, this, &MainWindow::handleExerciseReady);
    connect(m_controller, &AppController::unitProgress, this, &MainWindow::handleUnitProgress);
    connect(m_controller, &AppController::resultReady, this, &MainWindow::handleResult);
    connect(m_controller, &AppController::unitCompleted, this, &MainWindow::handleUnitCompleted);
    connect(m_controller, &AppController::streamFinished, this, &MainWindow::handleStreamFinished);
    connect(m_controller, &AppController::streamsReady, [this]() {
        m_pathView->setStreams(&m_controller->streams());
    });
    connect(m_controller, &AppController::errorOccurred, this, &MainWindow::handleError);

    if (m_controller) {
        m_profileView->attachProfile(&m_controller->profile());
        m_pathView->attachProfile(&m_controller->profile());
        m_pathView->setStreams(&m_controller->streams());
    }
}

void MainWindow::handleResult(const Result& result) {
    m_lessonView->showResult(result.feedback + " (Score: " + QString::number(result.score) + ")");
}

void MainWindow::handleExerciseReady(const Exercise* exercise) {
    m_lessonView->setExercise(exercise);
    m_tabs->setCurrentWidget(m_lessonView);
}

void MainWindow::handleUnitCompleted(const QString& streamId, const QString& unitId, const QString& unitTitle) {
    Q_UNUSED(streamId)
    Q_UNUSED(unitId)
    UnitCompleteDialog dialog(QString("Unit Complete: %1").arg(unitTitle), this);
    connect(&dialog, &UnitCompleteDialog::continueRequested, m_controller, &AppController::continueToNextUnit);
    dialog.exec();
}

void MainWindow::handleStreamFinished(const QString& streamId) {
    QMessageBox::information(this, "Stream Complete", QString("You've finished the %1 path!").arg(streamId));
    m_tabs->setCurrentWidget(m_homeView);
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

void MainWindow::handleUnitProgress(int current, int total) {
    m_lessonView->setUnitProgress(current, total);
}
