# Arcade Game Project

**Author:** Me Morfin  
**Title:** Arcade Game Project (for now)

## Description

An aspiring adventurer has decided to descend down a mysterious dungeon. It's been said, that it would bring great riches to the one who conquers it first.

Player will take control over the main character who aspires to do exactly that: conquer the dungeon.

This would be a rougelite game, with heavy emphasis on moving character in order to avoid enemies or their attacks, and maximizing player character's attack output capabilities.

## Game mechanics

### ~~Pushing the treasure~~

~~Gold, jewels and this kind of stuff has no value inside the dungeon, but why should they waste? Player has to push a cart from point A to B on each floor. The cart collects automatically all treasures that enemies have dropped. But it won't move at all if player is not around it. What's worse, if player is away form the cart for too long, cart will start moving backwards. Cart won't move forward if enemies are around it, no matter if player is attempting to push it. (It's additional role is to track player's score.)~~

### Randomized dungeon floors

Each floor of the dungeon will be randomized. But each will be generated in such a way, that it must be possible to finish it. 
- The part about it being possible doesn't include the difficulty of the enemies, only whether player can realistically go from start to finish.
- The sidegoals if implemented, also have to be possible to complete.
The general idea is, that the game will generate (or choose from predefined) rooms or chambers. It should then put them all on top of each other, then iterate over each of them and move them slightly away from each other, untill none of them overlap with each other, nor is too close (not sure about this one yet). At the very end, program should create some corridoors between rooms, so it is possible to pathfind from andy to any room.
- It may be a good idea to see if it is possible to make the corridoors a little bid redundant in their numbers, so it can limit the amount of backtracking, that the player would have to undergo to complete given dungeon floor.

### Build your own spells (with auto aim)

Heavily inspired mechanic by game the _Noita_. 

Player starts with 1 simple/weak way of attacking. (Maybe it will be possible to customize what it will be before starting each run). Then, as player progresses through the duneon floors, player will be able to unlock new attack pieces. It will be possible to customize then the attack, by rearranging, adding or removing from the attack pattern. The attack pattern is the actual attack that the character will attempt to perform with each attach. But, the main character starts pretty inexpeirenced, so there will be limit to how much can given attack do. For example, player will have to level up their character, so the character can use an attack pattern that aims to use more than 1 projectile. The attack pattern may still try to use more, but the extra projectiles won't be spawned into the world, unless the player character is capable of using those.

### Progressively increasing difficulty level

Concept as simple as scaling amount, speed, damage and health of enemies based on how many dungeon floors have player ventured in deep, ~~how much time has passed since the beinning~~, ~~and how high is player's level~~.

### Dungeon floor awareness

A dunegon floor awareness system will be implemented. 

The more enemies the player character defeats, and the mode rooms in the dungeon have lost their guardians, the higher the duneon floor's awareness about the player.

Once the awareness reaches 100% for the given floor, all of the present enemies will learn player character's current position and will attempt to get a revenge on the player.

## Level design

All levels are being randomly generated.

There will be a pool of predefined rooms, enemies and such, but in general, it can be though as if it was just a big remix of all or a subsection of available to the generator puzzles. As the difficulty of the game increases, the levels will be getting bigger or more difficult than the previous ones.

## Graphics

In the initial version of the game, the game is utilizing some free assets from itch.io. Authors of those assets are credited int this project for as long as those assets will be used.

See `resources/sources.md` for full list of used assets.

In case that some URLs get out of date for assets that are still being used, please make a new issue on this github repo, if there isn't one open regarding this already. Thanks.

### Intro/Outro

### UI/UX

**WIP**  
This part will be either omited or implemented with library ImGui if I figure out, how to attach this library to the projet.

## Programming

It will be written in C++. 

### Shaders

Those will be written in GLSL.

### External libraries

The project will use: 
- **SDL3** - the media layer
- **Glad** - access to OpenGL
- **ImGui** - interface
- **GLM** - OpenGL math
- **stb_image** - loading images

## Sound

Either the game will use some free sounds from free resource packs around the internet, or it won't use any at all, or some kind soul will contribute some music or sound effects for this project.

### SFX

### Music

## Story and narration

In the early version of the game it will be lacking the story. Sorry it that's something you really hoped for.

## Implemented technologies

### Used tools

The project will be build with help of CMake.

### Targeted platforms

It is intended to be played on PCs, on Windows and Linux platforms.

### Game engine

Game will be build wihtout an actual engine.  

**\>:)**

### Additional tools

I am planning on using the following tools:
- GIMP
- Inkscape
- Blender

## External resources

## Dystribution

Initially it will be available on this github page, for as long as I think it's reasonable. I may set this repository to private after some time, but after some time thinking, this is better suited to be an open source thing, that I can showcase as a part of my portfolio.

If this project happens to be any good, I will make a page on itch.io for it. If it gets real public interest, I will attempt to put it on steam.
