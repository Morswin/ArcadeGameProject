# Arcade Game Project
## Author
## Title
## Description
An aspiring adventurer has decided to descend down a mysterious dungeon. It's been said, that it would bring great riches to the one who conquers it first.
Player will take control over the main character who aspires to do exactly that: conquer the dungeon.
## Game mechanics
### Randomized dungeon floors
Each floor of the dungeon will be randomized. But each will be generated in such a way, that it must be possible to finish it. 
- The part about it being possible doesn't include the difficulty of the enemies, only whether player can realistically go from start to finish.
- The sidegoals if implemented, also have to be possible to complete.
The general idea is, that the game will generate (or choose from predefined) rooms or chambers. It should then put them all on top of each other, then iterate over each of them and move them slightly away from each other, untill none of them overlap with each other, nor is too close (not sure about this one yet). At the very end, program should create some corridoors between rooms, so it is possible to pathfind from andy to any room.
- It may be a good idea to see if it is possible to make the corridoors a little bid redundant in their numbers, so it can limit the amount of backtracking, that the player would have to undergo to complete given dungeon floor.
### Build your own spells (with auto aim)
Heavily inspired mechanic by game _Noita_. Player starts with 1 simple/weak way of attacking. (Maybe it will be possible to customize what it will be before starting each run). Then, as player progresses through the duneon floors, player will be able to unlock new attack pieces. It will be possible to customize then the attack, by rearranging, adding or removing from the attack pattern. The attack pattern is the actual attack that the character will attempt to perform with each attach. But, the main character starts pretty inexpeirenced, so there will be limit to how much can given attack do. For example, player will have to level up their character, so the character can use an attack pattern that aims to use more than 1 projectile. The attack pattern may still try to use more, but the extra projectiles won't be spawned into the world, unless the player character is capable of using those.
### Progressively increasing difficulty level
Concept as simple as scaling amount, speed, damage and healt of enemies based on how many dungeon floors have player verutred in, how much time has passed since the beinning, and how high is player's level.
## Level design
## Graphics
## Programming
## Sound
## Story and narration
## Implemented technologies
## External resources
## Dystribution
