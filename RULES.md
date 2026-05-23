# Prayas — Team Coding Rules
### text-based-rpg | KECKTM (IOE TU) | Year I Sem II

---

## 1. First Time Setup
Do this ONCE after joining the repo.

Clone the repo to your laptop:
```bash
git clone https://github.com/Prayas-10/text-based-rpg.git
```

Open it in VS Code:
```bash
cd text-based-rpg
code .
```

Create your branch — do this ONCE:
```bash
git checkout -b yourname/your-module
```

Examples:
```bash
git checkout -b pranjal/battle-system
git checkout -b prasanna/player-enemy
git checkout -b udison/inventory-items
git checkout -b saroj/ui
```

---

## 2. Daily Workflow
Do this EVERY time you code.

**Before coding — always pull first:**
```bash
git pull origin main
```

**After coding — save your work:**
```bash
git add src/YourFile.cpp
git commit -m "[module] what you did"
git push origin yourname/your-module
```

Full example for Pranjal:
```bash
git pull origin main
# write code in BattleSystem.cpp
git add src/BattleSystem.cpp
git commit -m "[battle] add player attack function"
git push origin pranjal/battle-system
```

---

## 3. Commit Message Format
```
[module] short description of what you did
```

**Your module tags:**
| Tag | Who uses it |
|-----|------------|
| `[game]` | TBD |
| `[battle]` | TBD |
| `[player]` | TBD |
| `[enemy]` | TBD |
| `[ui]` | TBD |
| `[inv]` | TBD |
| `[docs]` | Anyone |
| `[config]` | Rupesh only |

**Good examples:**
```
[battle] add turn based loop
[player] fix XP overflow on level up
[ui] add colored HP bar with block chars
[inv] implement useItem function
[docs] update storyline with Lhasa arc
```

**Bad examples — never do these:**
```
added stuff
changes
fix
final
aaa
```

---

## 4. File Ownership — Touch Only Yours
| File | Owner |
|------|-------|
| TBD | Rupesh |
| TBD | Pranjal |
| TBD | Prasanna |
| TBD | Prasanna |
| TBD | Udison |
| TBD | Udison |
| TBD | Saroj |

**Never touch someone else's file. Ever.**

---

## 5. How to Add Only Your File
Never use `git add .` — it adds everything.

Always specify your file:
```bash
# correct
git add src/BattleSystem.cpp

# correct — multiple files if you own both
git add src/Player.cpp src/Enemy.cpp

# WRONG — never do this
git add .
```

---

## 6. Branch Naming
```
yourname/what-you-are-doing
```

Examples:
```
pranjal/battle-loop
prasanna/player-stats
udison/inventory-system
saroj/hp-bar-ui
rupesh/game-loop
```

---

## 7. Opening a Pull Request
When your feature is done:

1. Push your branch to GitHub
2. Go to github.com/Prayas-10/text-based-rpg
3. Click **Compare & pull request**
4. Fill the template completely:
   - What did you change
   - Which file
   - Does it compile
   - What should be checked
   - Anything incomplete
5. Submit — Owner reviews and merges

---

## 8. Checking Repo Status
Useful commands to know where you are:

```bash
# see what files you changed
git status

# see recent commits
git log --oneline -5

# see which branch you are on
git branch

# go back to your branch if lost
git checkout yourname/your-module
```

---

## 9. Golden Rules
```
✅ Pull before coding — always
✅ Push only your file — always
✅ Code must compile before pushing
✅ Commit message in correct format
✅ Fill PR template completely

❌ Never git add .
❌ Never push to main
❌ Never touch someone else's file
❌ Never push broken code
❌ Never leave vague commit messages
```

---

## 10. When Something Goes Wrong
Don't panic. Don't push. Message Project Grp immediately.

Common problems:

**Accidentally edited wrong file:**
```bash
git checkout src/WrongFile.cpp
```
This restores the file to its last committed state.

**Pushed something wrong:**
```bash
# message Project Grp — they will fix it
```

**Merge conflict:**
```bash
# message Project Grp — they will fix it
```

---

## Repo
github.com/Prayas-10/text-based-rpg

## Questions
Message Project Grp on Viber.
