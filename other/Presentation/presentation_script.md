# Bhasha Quest Deliverable 3 — 8-Minute Script (Draft)
Audience: course evaluators. Style: concise, confident, pattern-focused. Total ~8:00.

## 0. Title (0:00–0:30)
“Welcome! This is Bhasha Quest, a dual-language learning app for Nepali and Kannada. I’m Hardik Shrestha. In 8 minutes I’ll show the architecture, patterns, key features, and tests that back the system.”

## 1. Problem & Goals (0:30–1:15)
- “We needed structured learning: two parallel streams, units of exactly three exercises, audio where available, and visible progression.”
- “A Path tab shows completed/current/locked units; an admin override allows jumps for demos or instructors.”
- “We track XP, streaks, and skills; we separate UI from domain to keep it maintainable.”

## 2. Architecture (1:15–2:30)
- “We use a layered MVC: UI → Controller → Domain → Data. The controller orchestrates grading, progress, and persistence.”
- “Repositories isolate persistence. Today we ship JSON for content and profile, with a SQLite profile repo ready behind the same interface.”
- “Signals/slots decouple UI from domain: LessonView emits submissions; AppController emits results, unit completion, and errors.”
- “Error handling: missing content/profile surfaces as errors; missing audio is ignored safely; bounds checks prevent out-of-range unit/exercise access.”

## 3. Design Patterns (2:30–3:45)
- Factory: “ExerciseFactory builds MCQ, Translate, TileOrder, Listen, Speak from JSON without sprawling conditionals—Open/Closed-friendly.”
- Singleton: “AudioManager centralizes QMediaPlayer/QAudioOutput, avoiding duplicate initializations.”
- Strategy: “Graders per exercise type; the controller picks at runtime, so adding CharacterSelection or Listen didn’t touch the controller logic.”
- Observer: “Profile is a Subject; ProfileView subscribes to stay in sync on XP/streak/unit completion without tight coupling.”

## 4. Feature Walkthrough (3:45–5:45)
- Home/Path: “Two streams, Nepali and Kannada. Path shows completed/current/locked units. Admin override uses password admin123.”
- Lesson: “MCQ now supports click-to-fill; character picker for script-based answers; audio button when audio is present; progress label shows position in the 3-exercise unit.”
- Unit completion: “On the third exercise we show a confetti animation and a ‘Keep Learning’ button to advance.”
- Profile: “Learner Hardik; XP/streak; skills list; +1 day button to simulate streak progression for testing.”

## 5. Content & Data (5:45–6:30)
- “Content is data-driven: streams → units → exercises in JSON. Each unit has exactly three exercises. Character sets are provided per language.”
- “Audio assets are referenced by relative paths; AudioManager resolves and plays them, skipping quietly if missing.”

## 6. Testing & Quality (6:30–7:15)
- “GoogleTest/GoogleMock are vendored; build target is bhashaquest_tests.”
- “We test Factory, all graders, SRSScheduler intervals, Profile XP/streak/unit completion, and JsonContentRepository load/error handling.”
- “Planned next: controller signal tests with mocked repositories to cover startup/error paths.”

## 7. Results, Reflection, Next (7:15–7:50)
- “Design held up: adding streams/units and new exercise types was straightforward thanks to Factory/Strategy.”
- “Trade-off: Speak is stubbed; SQLite is ready but not the primary backend yet.”
- “Next steps: real ASR for Speak, promote SQLite, richer Path UX, more gmock coverage.”

## 8. Closing (7:50–8:00)
“That’s Bhasha Quest: dual streams, structured units, clear progression, and tested core logic. Happy to dive deeper or show any flow again.”

## Slide Mapping (align with presentation_plan.md)
1 Title; 2 Goals; 3 Architecture; 4 Unit Flow; 5 Patterns; 6–9 Features; 10 Content/Data; 11 Testing; 12 Results/Reflection; 13 Closing.

## Demo Cues (time-permitting)
- Show Path lock and admin override.
- Run a unit: MCQ click-to-fill, character picker, audio.
- Show confetti on completion.
- Open Profile, press +1 day, watch streak increment.
