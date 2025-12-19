#include <gtest/gtest.h>

#include <QDir>
#include <QFile>
#include <QTextStream>

#include "core/data/JsonContentRepository.h"
#include "core/domain/LearningStream.h"

static QString writeTempContent(const QString& json) {
    const QString path = QDir::tempPath() + "/bq_content_test.json";
    QFile f(path);
    if (f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&f);
        out << json;
    }
    return path;
}

TEST(JsonContentRepositoryTest, LoadsStreamsAndUnits) {
    const QString json = R"({
      "streams": [
        {"id": "s1", "name": "Stream 1", "language": "L", "units": [
          {"id": "u1", "title": "Unit 1", "exercises": [
            {"type": "MCQ", "spec": {"id": "e1", "prompt": "p", "choices": ["a","b"], "correctIndex": 0}}
          ]}
        ]}
      ]
    })";
    QString path = writeTempContent(json);
    JsonContentRepository repo(path);
    QString err;
    auto streams = repo.loadStreams(&err);
    EXPECT_TRUE(err.isEmpty());
    ASSERT_EQ(static_cast<int>(streams.size()), 1);
    EXPECT_EQ(streams[0].unitCount(), 1);
}

TEST(JsonContentRepositoryTest, MissingFileSetsError) {
    JsonContentRepository repo("/nonexistent/file.json");
    QString err;
    auto streams = repo.loadStreams(&err);
    EXPECT_TRUE(streams.empty());
    EXPECT_FALSE(err.isEmpty());
}
