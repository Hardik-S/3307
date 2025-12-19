#include "HomeView.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

HomeView::HomeView(QWidget* parent)
    : QWidget(parent),
      m_nepaliButton(new QPushButton("Start Nepali", this)),
      m_kannadaButton(new QPushButton("Start Kannada", this)),
      m_profileButton(new QPushButton("View Profile", this)) {
    setStyleSheet("QWidget { background-color: #f7f7fb; }");
    auto* layout = new QVBoxLayout(this);
    auto* title = new QLabel("Bhasha Quest", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold;");

    auto* subtitle = new QLabel("Choose your language path and keep building momentum.", this);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color: #555; font-size: 14px;");

    auto* cardRow = new QHBoxLayout();
    auto* nepaliCard = new QWidget(this);
    auto* kannadaCard = new QWidget(this);
    nepaliCard->setStyleSheet("background: #fff3e0; border-radius: 12px; padding: 12px;");
    kannadaCard->setStyleSheet("background: #e3f2fd; border-radius: 12px; padding: 12px;");

    auto* nepaliLayout = new QVBoxLayout(nepaliCard);
    nepaliLayout->addWidget(new QLabel("Learn Nepali", nepaliCard));
    nepaliLayout->addWidget(new QLabel("Greetings, food, and numbers", nepaliCard));
    nepaliLayout->addWidget(m_nepaliButton);

    auto* kannadaLayout = new QVBoxLayout(kannadaCard);
    kannadaLayout->addWidget(new QLabel("Learn Kannada", kannadaCard));
    kannadaLayout->addWidget(new QLabel("Everyday phrases and basics", kannadaCard));
    kannadaLayout->addWidget(m_kannadaButton);

    cardRow->addWidget(nepaliCard);
    cardRow->addWidget(kannadaCard);

    layout->addWidget(title);
    layout->addWidget(subtitle);
    layout->addStretch(1);
    layout->addLayout(cardRow);
    layout->addWidget(m_profileButton);
    layout->addStretch(2);

    connect(m_nepaliButton, &QPushButton::clicked, this, [this]() { emit startStreamRequested("nepali"); });
    connect(m_kannadaButton, &QPushButton::clicked, this, [this]() { emit startStreamRequested("kannada"); });
    connect(m_profileButton, &QPushButton::clicked, this, &HomeView::profileRequested);
}
