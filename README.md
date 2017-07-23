# Boss Rush!
#### Team Fortress 2 Boss Rush Mode! A mode where true heroes fight in the world among the wicked, nasty, and overall cruel.

## Introduction
Boss Rush is pretty much my own version of Freak Fortress / Versus Saxton Hale and all of its branches. I'm building it from the ground up mostly for myself so that I can have a better and easier time taking care of a server that runs it, as well as just having a much more modular way of making bosses as well as other things involving the gamemode.

**Note that currently this mod is in the works. It is non-functional and does not have a release yet.**

## Build Statuses

#### Current Stable Build Status (SourceMod 1.8, Master Branch)
[![Master Build Status](https://travis-ci.org/GameMaster85/TF2-Boss-Rush.svg?branch=master)](https://travis-ci.org/GameMaster85/TF2-Boss-Rush)

#### Current Unstable Build Status (SourceMod 1.9, Dev Branch)
[![Dev Build Status](https://travis-ci.org/GameMaster85/TF2-Boss-Rush.svg?branch=dev)](https://travis-ci.org/GameMaster85/TF2-Boss-Rush)

## Dependancies

**[TF2 Items](https://forums.alliedmods.net/showthread.php?t=115100)** - [Build(s)](https://builds.limetech.io/?p=tf2items) - By asherkin

**[More Colors](https://forums.alliedmods.net/showthread.php?t=185016)** - [Build(s)](https://www.doctormckay.com/download/scripting/include/morecolors.inc) - By Dr. McKay

**[SteamTools](https://forums.alliedmods.net/forumdisplay.php?f=147)** - [Build(s)](https://builds.limetech.io/?p=steamtools) - By asherkin

**[Updater](https://forums.alliedmods.net/showthread.php?t=169095)** - [Build(s)](https://bitbucket.org/GoD_Tony/updater/downloads/) - By GoD-Tony

**[TF2 Attributes](https://forums.alliedmods.net/showthread.php?t=210221)** - [Build(s)](https://github.com/FlaminSarge/tf2attributes/releases) - By FlaminSarge

**[SourceMod Transitional Helpers](https://github.com/VoiDeD/sourcemod-transitional-helpers)** - By VoiDeD


## Features

Features that players will love.
* Bosses! Servers can provide you with bosses and pit the entire team against one! Imagine a sort of monoculus, but a player is actually controlling it! It's essentially a 1vsALL gamemode!

* Class Perks! Similar to Warcraft Source, you can pick and choose one perk with your class that can radically change the playstyle of it to fight the boss. Want to be the scout that had the abilities from Parkour Fortress? Maybe a Boxer Heavy that can do combos and link into defensive maneuvers to survive the boss? It's there and possible. **NOT IMPLEMENTED**

Features that devs will love.
* Bosses are coded as a derived methodmap from CTFPlayer, and almost every feature of the boss will use this method map, including it's own hooks that is automatically hooked to things like SDKHook_PostThink and SDKHook_OnTakeDamageAlive. To make a new boss, just make a method map that derives from the base boss method map, and it will be considered a boss with all features intact! With the basic features there, not much else you need to do other then to have fun developing your own boss.

* The abilities to modify and create your own "Perks" for each mercenary class through methodmaps. One of the things I really wanted to add in the whole gamemode of things was the ability to have a perk system similar to warcraft source for each merc class. Not only is there a base class for each mercenary with their own special hooks and functions (Double Jump, Rev Minigun), but deriving a method map from that allows you to easily add your own. **NOT IMPLEMENTED**

* The healthbar is personally cleaner and directly hooks into how the boss changes it's own health. The healthbar change it's value no matter what happens to the health of the boss, so you can set it to your heart's content and the healthbar will change suit. In addition, all bosses take 1 damage from everything so that weapons still do their effects, (Tests shown that hits from anything that applies effects don't apply when 0 damage is dealt, even if the damage instance is actually there) the boss takes the full damage in BossHealth, then the actual health is set to BossHealth.

* Pro-Transitional Development Practices. If you're like me and you love OOP, then most of my code is mostly written in MethodMaps. So you'll probably like that idea. Everything also feels pretty organized. Just remember, SourcePawn isn't OOP. Shh...