# Bhasha Quest Deliverable 3 — Presentation Plan (8 min)

## Flow (agreed)
1. Opening (0:30) — What is Bhasha Quest; dual Nepali/Kannada; units of 3.
2. Problem & Goals (0:45) — Motivation, requirements: dual streams, Path tab, admin override, audio, progress.
3. Architecture (1:15) — Layered MVC, module roles, unit progression flow, error handling.
4. Design Patterns (1:15) — Factory, Singleton, Strategy, Observer (why/where/benefit).
5. Feature Walkthrough (2:00) — Home/Path; Lesson (MCQ click-to-fill, character picker, audio); Unit completion confetti; Profile (Hardik, +1 day/streak); admin override.
6. Content & Data (0:45) — Streams/units, JSON schema, audio assets.
7. Testing & Quality (0:45) — gtest/gmock suites, coverage focus, gaps.
8. Results & Reflection (0:45) — Wins, trade-offs (Speak stub), extensibility (SQLite ready), next steps.
9. Closing (0:30) — Recap + Q&A.

## Slide Outline (for Canva)
1) Title — “Bhasha Quest: Dual-Stream Language Learning” (subtitle: Deliverable 3, author Hardik Shrestha).  
2) Goals & Requirements — bullets for dual streams, units of 3, Path, admin override, audio, progress.  
3) Architecture Overview — layered diagram callout (MVC, repositories, controller orchestrator).  
4) Unit Flow — simple sequence/steps for submit → grade → update → persist → celebrate.  
5) Patterns — four tiles: Factory, Singleton, Strategy, Observer (location + benefit).  
6) Features (Home/Path) — screenshots/placeholders: Path tab with lock/admin, stream cards.  
7) Features (Lesson) — MCQ click-to-fill, character picker, audio button, progress label.  
8) Features (Unit Completion) — confetti + “Keep Learning” CTA.  
9) Features (Profile) — Hardik, XP/streak, +1 day, skills list.  
10) Content & Data — JSON schema highlights; audio assets note.  
11) Testing — gtest/gmock summary table; mention controller mock plan.  
12) Results & Reflection — wins/trade-offs/next steps.  
13) Closing — recap + ask for questions.

## Demo Flow (during “Feature Walkthrough”)
- Start at Home → open Path tab; show completed/current/locked units; admin override prompt.  
- Launch a unit: MCQ click-to-fill, character picker (Nepali/Kannada), audio playback.  
- Finish 3rd exercise → confetti dialog → continue to next unit.  
- Open Profile: shows “Hardik”, XP/streak; press “+1 day” to increment streak/date.  
- (Optional) show JSON content snippet or audio file path to emphasize data-driven design.

## Notes for Presenter
- Keep pace: ~45–60 seconds per major section; reserve 30 seconds buffer.  
- Mention patterns are exercised in code (not just theoretical).  
- Call out robustness: error signals, audio safe failure, repository abstraction.  
- Testing: note current passing suites and planned controller mock coverage.  
- Future work: real Speak evaluator, SQLite promotion, richer Path UX.  
