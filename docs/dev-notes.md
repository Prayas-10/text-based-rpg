# Dev Notes — Prayas Team

## 2083-02-09
- First meeting
- Github Setup
- Organization created as "Prayas-10"
- Repo created as text-based-rpg
- Game Prologue discussed
- Game elements discussed
- Github pull request template created
- .gitignore added
- README.md formalized
- Folders and files were divided
- Next Meeting set for 2083-02-16
  
### Files and their Elements as of 2083-1-02-09
- #### .github
  - PULL_REQUEST_TEMPLATE.md (pull request template)
- #### docs
  - storyline.txt&emsp;&emsp;&emsp;&emsp;(plain storyline)
  - setting.txt&emsp;&emsp;&emsp;&emsp;(Time period, Initial building and storyflow elements)
  - essentials_for_rpg.txt&emsp;&emsp;&emsp;&emsp;(game essentials and planning)
  - dev-notes.md&emsp;&emsp;&emsp;&emsp;(includes notes from devs)
- #### include
  - includes all user-defined headers required for the game
- #### src
  - main.cpp&emsp;&emsp;&emsp;&emsp;(calls the game file and runs everything)
  - game.cpp&emsp;&emsp;&emsp;&emsp;(main menus, screen changing, module inclusion, state machine)
  - map.cpp&emsp;&emsp;&emsp;&emsp;(locations, locking and unlocking, atmosphere, NPC location)
  - player.cpp&emsp;&emsp;&emsp;&emsp;(Protagonist, Name, Title, Background, HP, XP, level, stats, story tracking, save and load)
  - enemy.cpp&emsp;&emsp;&emsp;&emsp;(information about enemy and their behaviour)
  - battlesystem.cpp&emsp;&emsp;&emsp;&emsp;(attack, use item, run, enemy attack and special moves, damage formula and randomness, victory and defeat)
  - inventory.cpp&emsp;&emsp;&emsp;&emsp;(store player items, add and remove items, use item, display and hide item, check item)
  - item.cpp&emsp;&emsp;&emsp;&emsp;(item name, effects, quantity, description, class, rarity)
  - ui.cpp&emsp;&emsp;&emsp;&emsp;(text colour, visual effects, print bars of hp and xp, nav bar, main game screen, opening screen, gameplay and combat screen, level up effects, victory and defeat effects, game completion screen)
  - tutorial.cpp&emsp;&emsp;&emsp;&emsp;(tutorial explaining controls and mechaisms)
