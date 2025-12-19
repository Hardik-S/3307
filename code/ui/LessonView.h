#pragma once

#include <QWidget>

class QLabel;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class QLineEdit;

class Exercise;
class CharacterSelectionWidget;

class LessonView : public QWidget {
    Q_OBJECT

public:
    explicit LessonView(QWidget* parent = nullptr);

    void setExercise(const Exercise* exercise);
    void setUnitProgress(int current, int total);

signals:
    void answerSubmitted(const QString& answer);
    void nextRequested();
    void playAudioRequested();

public slots:
    void showResult(const QString& message);

private slots:
    void handleSubmit();
    void handleNext();
    void handleCharacterSelectionChanged(const QString& value);
    void handleChoiceClicked(QListWidgetItem* item);

private:
    void updateForExerciseType(const Exercise* exercise);
    QString currentAnswer() const;

    const Exercise* m_exercise;
    QLabel* m_promptLabel;
    QLabel* m_progressLabel;
    QLabel* m_resultLabel;
    QListWidget* m_choiceList;
    QLabel* m_hintLabel;
    QLineEdit* m_answerInput;
    CharacterSelectionWidget* m_characterWidget;
    QPushButton* m_submitButton;
    QPushButton* m_nextButton;
    QPushButton* m_playButton;
};
