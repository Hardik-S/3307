#pragma once

#include <QString>
#include <QStringList>

class Exercise {
public:
    explicit Exercise(const QString& id, const QString& prompt);
    virtual ~Exercise() = default;

    QString id() const;
    QString prompt() const;

    virtual QString type() const = 0;
    virtual QStringList choices() const;
    virtual QString correctAnswer() const;
    virtual QString audioPath() const;
    virtual bool usesCharacterSelection() const;

private:
    QString m_id;
    QString m_prompt;
};
