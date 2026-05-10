# 3307 BhashaQuest

BhashaQuest is a Qt/C++ course project for practicing Nepali and Kannada learning streams. The app includes a desktop UI, JSON-backed course content, audio exercises, profile persistence, spaced-repetition helpers, and a written project report.

## Repository Layout

- `code/` - Qt application source for the `BhashaQuest` desktop app.
- `code/core/` - Domain, data, and controller code.
- `code/ui/` - Qt widgets and main-window views.
- `code/assets/audio/` - Audio clips used by listen exercises.
- `code/core/data/content.json` - Bundled learning stream content copied beside the app at build time.
- `code/tests/` - Qt console test project for domain and repository tests.
- `report/` - Final PDFs, LaTeX report source, and generated report images.
- `other/` - Course notes, planning files, presentation scripts, and study material.

## Build The App

Use Qt Creator or a Qt command prompt with qmake available:

```powershell
cd code
qmake BhashaQuest.pro
nmake
```

The qmake project copies `content.json` and `assets/` into the debug or release output folder after linking so the app can load bundled content locally.

## Run Tests

The test harness is defined in `code/tests/tests.pro`:

```powershell
cd code/tests
qmake tests.pro
nmake
.\debug\bhashaquest_tests.exe
```

`tests.pro` expects GoogleTest/GoogleMock sources under `code/tests/googletest/`. If that directory is missing, add the dependency checkout before building the test target.

## Current Scope

Implemented exercise types include MCQ, translation, tile ordering, listen, and a stubbed speak evaluator. JSON profile/content repositories are active, SQLite support is present for future persistence work, and `code/NextSteps.md` tracks remaining follow-ups such as real ASR capture, richer tile ordering, and expanded repository/controller coverage.
