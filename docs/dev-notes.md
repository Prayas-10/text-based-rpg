# Dev Notes — Prayas Team

## First Meeting (2083-02-09)
- First meeting
- Github Setup
- Organization created as **"Prayas-10"**
- Repo created as **text-based-rpg**
- Game Prologue discussed
- Game elements discussed
- Github pull request template created
- **.gitignore** added
- **README.md** formalized
- Folders and files were divided
  <br><br>
***[Next Meeting set for 2083-02-16]***
  
### Files and their Elements as of 2083-1-02-09
- #### .github
  | File Name | Remarks |
  |----|----| 
  | PULL_REQUEST_TEMPLATE.md | pull request template |
  |CODEOWNERS | shows who is responsible for which part |
  - ##### ISSUE TEMPLATE
      | File Name | Remarks |
      |----|----| 
      | tast.md | tells the question to be answered each commit |
  - ##### workflows
      | File Name | Remarks |
      |----|----| 
      | build-check.yml | builds everything when pushed into github |
      | commit-check.yml | checks commit format in each commit |
- #### docs
    | File Name | Remarks |
  |----|----| 
  | storyline.txt | plain storyline |
  | setting.txt | Time period, Initial building and storyflow elements |
  | essentials_for_rpg.txt | game essentials and planning |
  | dev-notes.md | includes notes from devs |
- #### include
  - includes all user-defined headers required for the game
- #### src
    | File Name | Remarks |
  |----|----| 
  | main.cpp | calls the game file and runs everything |
  | game.cpp | main menus, screen changing, module inclusion, state machine |
  | map.cpp | locations, locking and unlocking, atmosphere, NPC location |
  | player.cpp | Protagonist, Name, Title, Background, HP, XP, level, stats, story tracking, save and load |
  | enemy.cpp | information about enemy and their behaviour |
  | battlesystem.cpp | attack, use item, run, enemy attack and special moves, damage formula and randomness, victory and defeat |
  | inventory.cpp | store player items, add and remove items, use item, display and hide item, check item|
  | item.cpp | item name, effects, quantity, description, class, rarity|
  | ui.cpp | text colour, visual effects, print bars of hp and xp, nav bar, main game screen, opening screen, gameplay and combat screen, level up effects, victory and defeat effects, game completion screen |
  | tutorial.cpp | tutorial explaining controls and mechaisms |
- #### RULES.md
  - Rules to be followed
- #### README.md
  - Team and project info
- #### .gitignore
  - prevent pushing unwanted file types


---

 ## Rupesh (2083-02-10)
  ### Files Added
  - constants.h
  - enemy.h
  - battlesystem.h
  - inventory.h
  - items.h 
  - map.h
  - player.h
  - tutorial.h
  - ui.h
  <br><br>
  ***Stub code added to all files in include folder and src folder***

  ---

## Second Meeting (2083-02-16)
- Prologue decided
- Scene one decided
- First division of modules
| Name | Modules |
|------|---------|
|Rupesh Joshi|main.cpp, game.cpp, player.cpp|
|Pranjal Khanal|ui.cpp, prologue.cpp|
|Udison Mulmi Shrestha|map.cpp|
