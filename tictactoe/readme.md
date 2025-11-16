## AI feedback as of commit 72808c1

### Quick, practical improvements (do these first)

1. **Fix draw detection** — right now the game never ends if board fills with no winner. Add a simple check for a full board and return a draw. (Small change in `boardIsGameOver()`.)
2. **Basic input validation** — check `cin` success and whether `x,y` are in range before calling `boardPlacePlayer()`. If invalid, clear `cin` and prompt again. (Avoids crashes or infinite loops on bad input.)
3. **Clarify coordinate system** — decide 0-based or 1-based and show it in the prompt. E.g., “Enter row and column (1–3):”. This reduces user confusion.
4. **Avoid leaking core resources** — minimal: add a `Game` destructor to `delete` objects (or create `Board` and `Player` as stack members). You don’t have to convert to smart pointers immediately; just ensure no leaks for the shipped repo.
5. **Initialize members** — set `curTeam` in `Player` constructor initializer list to a known value (or require it in constructor) to avoid any accidental uninitialized use.
6. **Make error messages actionable** — when move is invalid, print why (out of range OR cell occupied). Small UX win for testers.

### Low-effort quality-of-life items (nice-to-have)

1. **“Play again?” loop** — ask user at the end if they want another game and reset the board (preserve player stats). Very small change and makes repo friendlier.
2. **Show coordinates on board display** — print row/col numbers alongside the cells so input is intuitive.
3. **Replace `#define` with `constexpr`** — `constexpr char EMPTY_CELL = '-';` — tiny modernizing change, no big refactor.
4. **Replace `usleep` with portable sleep** only if you expect Windows support; otherwise ok to keep for Linux builds. (If you keep `usleep`, guard with `#ifdef` or document platform.)

### Reasonable issues (what’s actually problematic)

1. **No draw detection** — functional bug; must fix.
2. **Unvalidated input** — fragile for real users.
3. **Memory ownership is unclear** — you `new` objects but don’t delete them; not catastrophic for a short-lived program but worth tidying.
4. **UI + logic tightly coupled** — fine for a small program, but makes automated testing harder.
5. **Inconsistent naming / small style nits** — `boardDisplay`, `boardPlacePlayer` etc. — they work but can be smoothed later if you care.

### Practical features you can add (small steps, not overkill)

1. **Single-player AI (easy)** — implement a random valid move or simple rule-based move (block opponent or win if possible). Minimax is optional; start simple.
2. **Undo last move** — keep a small move stack and let user undo one move. Good for demos.
3. **Save basic stats to disk** — write wins/games to a small text file so your GitHub demo shows persistence. Keep it simple (one-per-line, no DB).
4. **Command-line flags** — `--size 4` to allow NxN boards (optional). If you keep code modular, this is straightforward.
5. **Unit test for Board logic** — just a couple of asserts for row/col/diag/draw. Small and shows test-awareness.

### Class organization — keep it simple and achievable

1. Your current split (Board / Player / Game) is **good and reasonable** for a small personal repo. It communicates intent and is easy for reviewers to follow.
2. Small cleanup recommendations (no big refactor):

   * Keep `Board` as the **single source of truth** for cell state & win/draw checks. Do **not** put I/O there — leave display calls in `Game` for now.
   * `Game` can keep simple turn loop and `cin`/`cout` interactions. That’s fine; no need to extract a UI class unless you plan to add GUI or tests.
   * Make ownership clear: either `Game` owns `Board`/`Player` as stack members, or make them `unique_ptr`s. For now, simplest: construct them as members (no `new`), e.g. `Board b; Player p1;` — small and safe.
3. Aim for **small, incremental improvements** rather than big design changes. For a first GitHub project, clarity beats over-engineering.

### Tiny suggested README notes to add to GitHub

* One-line description.
* How to build and run (commands).
* Known limitations (e.g., "3x3 only", "input expects integers", "no persistent stats yet" — update as you add features).
* What you plan next (draw detection fix, save stats, simple AI). Helps interviewers see thought process.

---