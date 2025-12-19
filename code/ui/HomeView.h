#pragma once

#include <QWidget>

class QPushButton;

class HomeView : public QWidget {
    Q_OBJECT

public:
    explicit HomeView(QWidget* parent = nullptr);

signals:
    void startStreamRequested(const QString& streamId);
    void profileRequested();

private:
    QPushButton* m_nepaliButton;
    QPushButton* m_kannadaButton;
    QPushButton* m_profileButton;
};
