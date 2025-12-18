#include "LessonView.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "core/domain/Exercise.h"
#include "core/domain/ListenExercise.h"
#include "core/domain/TileOrderExercise.h"
#include "core/domain/TranslateExercise.h"
#include "ui/widgets/CharacterSelectionWidget.h"

LessonView::LessonView(QWidget* parent)
    : QWidget(parent),
      m_exercise(nullptr),
      m_promptLabel(new QLabel(this)),
      m_resultLabel(new QLabel(this)),
      m_choiceList(new QListWidget(this)),
      m_hintLabel(new QLabel(this)),
      m_answerInput(new QLineEdit(this)),
      m_characterWidget(new CharacterSelectionWidget(this)),
      m_submitButton(new QPushButton("Submit", this)),
      m_nextButton(new QPushButton("Next", this)),
      m_playButton(new QPushButton("Play Audio", this)) {
    m_promptLabel->setWordWrap(true);
    m_resultLabel->setStyleSheet("font-weight: bold; color: #1b5e20;");
    m_hintLabel->setStyleSheet("color: #666;");

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(m_promptLabel);
    layout->addWidget(m_playButton);
    layout->addWidget(m_choiceList);
    layout->addWidget(m_hintLabel);
    layout->addWidget(m_answerInput);
    layout->addWidget(m_characterWidget);

    auto* buttonRow = new QHBoxLayout();
    buttonRow->addWidget(m_submitButton);
    buttonRow->addWidget(m_nextButton);
    layout->addLayout(buttonRow);
    layout->addWidget(m_resultLabel);
    layout->addStretch(1);

    connect(m_submitButton, &QPushButton::clicked, this, &LessonView::handleSubmit);
    connect(m_nextButton, &QPushButton::clicked, this, &LessonView::handleNext);
    connect(m_playButton, &QPushButton::clicked, this, &LessonView::playAudioRequested);
    connect(m_characterWidget, &CharacterSelectionWidget::selectionChanged, this, &LessonView::handleCharacterSelectionChanged);

    m_choiceList->setVisible(false);
    m_playButton->setVisible(false);
    m_characterWidget->setVisible(false);
    m_nextButton->setEnabled(false);
}

void LessonView::setExercise(const Exercise* exercise) {
    m_exercise = exercise;
    m_resultLabel->clear();
    m_nextButton->setEnabled(false);
    m_answerInput->clear();
    m_characterWidget->clear();
    updateForExerciseType(exercise);
}

void LessonView::updateForExerciseType(const Exercise* exercise) {
    if (!exercise) {
        return;
    }

    m_promptLabel->setText(exercise->prompt());
    m_choiceList->clear();
    m_choiceList->setVisible(false);
    m_playButton->setVisible(false);
    m_answerInput->setVisible(true);
    m_answerInput->setReadOnly(false);
    m_characterWidget->setVisible(false);
    m_hintLabel->clear();

    if (exercise->type() == "MCQ" || exercise->type() == "Listen") {
        const auto choices = exercise->choices();
        for (int i = 0; i < choices.size(); ++i) {
            m_choiceList->addItem(QString::number(i + 1) + ". " + choices[i]);
        }
        m_choiceList->setVisible(true);
        m_hintLabel->setText("Type the option number.");
        m_answerInput->setPlaceholderText("e.g., 1");
    }

    if (exercise->type() == "Listen") {
        m_playButton->setVisible(true);
    }

    if (exercise->type() == "Translate") {
        const auto* translate = dynamic_cast<const TranslateExercise*>(exercise);
        if (translate && translate->usesCharacterSelection()) {
            m_answerInput->setReadOnly(true);
            m_characterWidget->setVisible(true);
            m_hintLabel->setText("Select characters to build the answer.");
        } else {
            m_answerInput->setReadOnly(false);
            m_hintLabel->setText("Type your translation.");
        }
    }

    if (exercise->type() == "TileOrder") {
        const auto* tile = dynamic_cast<const TileOrderExercise*>(exercise);
        if (tile) {
            m_hintLabel->setText("Order the tiles separated by commas.");
            m_answerInput->setPlaceholderText(tile->choices().join(", "));
        }
    }

    if (exercise->type() == "Speak") {
        m_hintLabel->setText("Type what you said (stub evaluation).");
        m_answerInput->setPlaceholderText("Transcript...");
    }
}

QString LessonView::currentAnswer() const {
    if (m_exercise && m_exercise->type() == "Translate") {
        const auto* translate = dynamic_cast<const TranslateExercise*>(m_exercise);
        if (translate && translate->usesCharacterSelection()) {
            return m_characterWidget->selection();
        }
    }
    return m_answerInput->text();
}

void LessonView::handleSubmit() {
    emit answerSubmitted(currentAnswer());
}

void LessonView::handleNext() {
    emit nextRequested();
}

void LessonView::handleCharacterSelectionChanged(const QString& value) {
    m_answerInput->setText(value);
}

void LessonView::showResult(const QString& message) {
    m_resultLabel->setText(message);
    m_nextButton->setEnabled(true);
}
