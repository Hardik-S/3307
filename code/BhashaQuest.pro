QT += core gui widgets multimedia sql
CONFIG += c++17
TEMPLATE = app
TARGET = BhashaQuest

INCLUDEPATH += .

HEADERS += \
    ui/MainWindow.h \
    ui/HomeView.h \
    ui/LessonView.h \
    ui/PathView.h \
    ui/ProfileView.h \
    ui/UnitCompleteDialog.h \
    ui/widgets/CharacterSelectionWidget.h \
    core/controllers/AppController.h \
    core/data/IContentRepository.h \
    core/data/JsonContentRepository.h \
    core/data/IProfileRepository.h \
    core/data/JsonProfileRepository.h \
    core/data/SQLiteProfileRepository.h \
    core/domain/AudioManager.h \
    core/domain/CharacterUtils.h \
    core/domain/Exercise.h \
    core/domain/MCQExercise.h \
    core/domain/TranslateExercise.h \
    core/domain/TileOrderExercise.h \
    core/domain/ListenExercise.h \
    core/domain/SpeakExercise.h \
    core/domain/ExerciseFactory.h \
    core/domain/Result.h \
    core/domain/StrategyGrader.h \
    core/domain/MCQGrader.h \
    core/domain/TranslateGrader.h \
    core/domain/TileOrderGrader.h \
    core/domain/ListenGrader.h \
    core/domain/SpeakGrader.h \
    core/domain/CharacterSelectionGrader.h \
    core/domain/Observer.h \
    core/domain/Subject.h \
    core/domain/Unit.h \
    core/domain/LearningStream.h \
    core/domain/Profile.h \
    core/domain/SkillProgress.h \
    core/domain/SRSScheduler.h \
    core/domain/StubSpeechEvaluator.h

SOURCES += \
    main.cpp \
    ui/MainWindow.cpp \
    ui/HomeView.cpp \
    ui/LessonView.cpp \
    ui/PathView.cpp \
    ui/ProfileView.cpp \
    ui/UnitCompleteDialog.cpp \
    ui/widgets/CharacterSelectionWidget.cpp \
    core/controllers/AppController.cpp \
    core/data/JsonContentRepository.cpp \
    core/data/JsonProfileRepository.cpp \
    core/data/SQLiteProfileRepository.cpp \
    core/domain/AudioManager.cpp \
    core/domain/CharacterUtils.cpp \
    core/domain/Exercise.cpp \
    core/domain/ExerciseFactory.cpp \
    core/domain/MCQExercise.cpp \
    core/domain/TranslateExercise.cpp \
    core/domain/TileOrderExercise.cpp \
    core/domain/ListenExercise.cpp \
    core/domain/SpeakExercise.cpp \
    core/domain/MCQGrader.cpp \
    core/domain/TranslateGrader.cpp \
    core/domain/TileOrderGrader.cpp \
    core/domain/ListenGrader.cpp \
    core/domain/SpeakGrader.cpp \
    core/domain/CharacterSelectionGrader.cpp \
    core/domain/Profile.cpp \
    core/domain/SkillProgress.cpp \
    core/domain/SRSScheduler.cpp \
    core/domain/StubSpeechEvaluator.cpp \
    core/domain/Subject.cpp \
    core/domain/Unit.cpp \
    core/domain/LearningStream.cpp

# Copy content and assets to build output for local loading
CONFIG(debug, debug|release) {
    unix: QMAKE_POST_LINK += cp $$shell_quote($$PWD/core/data/content.json) $$shell_quote($$OUT_PWD/content.json) $$escape_expand(\n\t)
    unix: QMAKE_POST_LINK += cp -r $$shell_quote($$PWD/assets) $$shell_quote($$OUT_PWD/assets) $$escape_expand(\n\t)
    win32: QMAKE_POST_LINK += copy /Y $$shell_quote($$shell_path($$PWD/core/data/content.json)) $$shell_quote($$shell_path($$OUT_PWD/debug/content.json)) $$escape_expand(\n\t)
    win32: QMAKE_POST_LINK += xcopy /Y /E /I $$shell_quote($$shell_path($$PWD/assets)) $$shell_quote($$shell_path($$OUT_PWD/debug/assets)) $$escape_expand(\n\t)
}
CONFIG(release, debug|release) {
    unix: QMAKE_POST_LINK += cp $$shell_quote($$PWD/core/data/content.json) $$shell_quote($$OUT_PWD/content.json) $$escape_expand(\n\t)
    unix: QMAKE_POST_LINK += cp -r $$shell_quote($$PWD/assets) $$shell_quote($$OUT_PWD/assets) $$escape_expand(\n\t)
    win32: QMAKE_POST_LINK += copy /Y $$shell_quote($$shell_path($$PWD/core/data/content.json)) $$shell_quote($$shell_path($$OUT_PWD/release/content.json)) $$escape_expand(\n\t)
    win32: QMAKE_POST_LINK += xcopy /Y /E /I $$shell_quote($$shell_path($$PWD/assets)) $$shell_quote($$shell_path($$OUT_PWD/release/assets)) $$escape_expand(\n\t)
}
