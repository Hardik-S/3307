QT += core
CONFIG += c++17 console testcase qt
TEMPLATE = app
TARGET = bhashaquest_tests

GTEST_DIR = $$PWD/googletest

INCLUDEPATH += .. \
    ../core \
    ../core/domain \
    ../core/data \
    $$GTEST_DIR/googletest \
    $$GTEST_DIR/googlemock \
    $$GTEST_DIR/googletest/include \
    $$GTEST_DIR/googlemock/include

SOURCES += \
    TestMain.cpp \
    TestExerciseFactory.cpp \
    TestGraders.cpp \
    TestSRSScheduler.cpp \
    TestProfile.cpp \
    TestContentRepository.cpp \
    $$GTEST_DIR/googletest/src/gtest-all.cc \
    $$GTEST_DIR/googlemock/src/gmock-all.cc \
    ../core/domain/Exercise.cpp \
    ../core/domain/MCQExercise.cpp \
    ../core/domain/TranslateExercise.cpp \
    ../core/domain/TileOrderExercise.cpp \
    ../core/domain/ListenExercise.cpp \
    ../core/domain/SpeakExercise.cpp \
    ../core/domain/ExerciseFactory.cpp \
    ../core/domain/MCQGrader.cpp \
    ../core/domain/TranslateGrader.cpp \
    ../core/domain/TileOrderGrader.cpp \
    ../core/domain/ListenGrader.cpp \
    ../core/domain/SpeakGrader.cpp \
    ../core/domain/CharacterSelectionGrader.cpp \
    ../core/domain/SkillProgress.cpp \
    ../core/domain/Profile.cpp \
    ../core/domain/SRSScheduler.cpp \
    ../core/domain/StubSpeechEvaluator.cpp \
    ../core/domain/Subject.cpp \
    ../core/domain/Unit.cpp \
    ../core/domain/LearningStream.cpp \
    ../core/data/JsonContentRepository.cpp

HEADERS += \
    ../core/domain/Exercise.h \
    ../core/domain/MCQExercise.h \
    ../core/domain/TranslateExercise.h \
    ../core/domain/TileOrderExercise.h \
    ../core/domain/ListenExercise.h \
    ../core/domain/SpeakExercise.h \
    ../core/domain/ExerciseFactory.h \
    ../core/domain/MCQGrader.h \
    ../core/domain/TranslateGrader.h \
    ../core/domain/TileOrderGrader.h \
    ../core/domain/ListenGrader.h \
    ../core/domain/SpeakGrader.h \
    ../core/domain/CharacterSelectionGrader.h \
    ../core/domain/SkillProgress.h \
    ../core/domain/Profile.h \
    ../core/domain/SRSScheduler.h \
    ../core/domain/StubSpeechEvaluator.h \
    ../core/domain/Subject.h \
    ../core/domain/Unit.h \
    ../core/domain/LearningStream.h \
    ../core/data/JsonContentRepository.h
