#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;
class QGridLayout;

class CharacterSelectionWidget : public QWidget {
    Q_OBJECT

public:
    explicit CharacterSelectionWidget(QWidget* parent = nullptr);

    QString selection() const;
    void clear();
    void setCharacters(const QStringList& characters);

signals:
    void selectionChanged(const QString& value);

private slots:
    void appendCharacter();
    void backspace();
    void clearSelection();

private:
    void setSelection(const QString& value);
    void rebuildGrid();

    QString m_selection;
    QLineEdit* m_display;
    QPushButton* m_backspaceButton;
    QPushButton* m_clearButton;
    QGridLayout* m_gridLayout;
    QStringList m_characters;
};
