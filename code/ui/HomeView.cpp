#include "HomeView.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

HomeView::HomeView(QWidget* parent)
    : QWidget(parent),
      m_startButton(new QPushButton("Start Lesson", this)),
      m_profileButton(new QPushButton("View Profile", this)) {
    auto* layout = new QVBoxLayout(this);
    auto* title = new QLabel("Bhasha Quest", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold;");

    layout->addWidget(title);
    layout->addStretch(1);
    layout->addWidget(m_startButton);
    layout->addWidget(m_profileButton);
    layout->addStretch(2);

    connect(m_startButton, &QPushButton::clicked, this, &HomeView::startLessonRequested);
    connect(m_profileButton, &QPushButton::clicked, this, &HomeView::profileRequested);
}
