[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)
# HACK4CSGO :zap:
First of all, if you are enough kind to motivate me, just **star** this project :) I would be very happy.

This is an internal cheat for **_Counter-Strike: Global Offensive_** I've been working on as my training of reverse engineering.
Since I don't intend to make this a malicious software, **this isn't considered to be performed in multi player mode**. Keep in that mind.

Besides that, I'm not a skilled hacker as this cheat is not a high quality as of today. However, It may be interesting for you to see this project evolving day by day. (me as well XD)

If you have any question about this project, feel free to ask me through [issue](https://github.com/s3pt3mb3r/HACK4CSGO/issues).

### STILL WORKING: August 02, 2020

# Support me :two_hearts:
Any supports will be greatly appreciated. 
You can easily support/motivate me by either **starring my project**, **following me on github** or **sending PR to me**.

# Table of contents :pushpin:

- [How to build this hack](#how-to-build-this-hack-syringe)
    - [Warning](#warning-rotating_light)
- [Menu](#menu-scroll)
- [Hacks](#hacks-computer)
    - [Aimbot](#aimbot)
    - [Glow hack](#glow-hack)
    - [Trigger bot](#trigger-bot)
    - [Neutralize recoil](#neutralize-recoil)
- [Features being developed](#features-being-developed)
- [Contributors](#contributors)


# How to build this hack :syringe:

**requirement**
- [DirectxSDK](https://www.microsoft.com/en-au/download/details.aspx?id=6812)

You can select from two ways to build this hack.
I believe all you need in order to build this project except DirectxSDK is already included which is [MSDetour](https://github.com/microsoft/Detours), [ImGui](https://github.com/ocornut/imgui), and [toml11](https://github.com/ToruNiina/toml11).
They're in Dependencies directory.

**1. Build project using Cmake**

Run these commands below.

```
$ git clone https://github.com/s3pt3mb3r/HACK4CSGO.git
$ cd HACK4CSGO
$ mkdir build && cd build
$ cmake ..
$ make
```

Then your `HACK4CSGO.dll` should be in `/build` directory.

**2. Build project using Visual Studio 2019**

If you still have cmake, carry out following commands. (No? Then scroll down a bit)

```
$ git clone https://github.com/s3pt3mb3r/HACK4CSGO.git
$ cd HACK4CSGO
$ mkdir build && cd build
$ cmake .. -A Win32
```

You can find `HACK4CSGO.sln` in `/build` directory.

Once you load the project click `Build` -> `Build HACK4CSGO`.

Then your `HACK4CSGO.dll` should be in `/build/Debug` directory.

You reject to install cmake? Check [releases](https://github.com/s3pt3mb3r/HACK4CSGO/releases) and download relevant zip file.
(If latest release looks old, create an issue and ask me, I'll handle it.)

**Either way you get the `HACK4CSGO.dll`, you can now inject it to the game with any DLL injector such as [GH injector](https://guidedhacking.com/resources/guided-hacking-dll-injector.4/) :)**

### WARNING :rotating_light:

Keep your eyes on the `offset.h` in my repository.

If the menu doesn't show up when you press INSERT, or your game crashes immediately just after you initiate the hack, that means your `offset.h` is outdated.

Copy and Paste contents in `offset.h` from mine to yours. Or if mine doesn't look updated, copy from [Hazedumper](https://github.com/frk1/hazedumper/blob/master/csgo.hpp)

# Menu :scroll:

You're accessible to the hack menu by pressing **INSERT** key on your keyboard.
**But you're allowed to access it only when you're in game. Even though you press INSERT when you are in main menu, nothing happens.**

![Hack menu](https://user-images.githubusercontent.com/33578715/89070761-09c39300-d3a8-11ea-9aac-18cf2749b622.gif)

You can toggle on/off and tweak parameters in the tabs with the name of each hack.

# Hacks :computer:
I've already been supporting a few hacks but unfortunately they're really like...under construction.

Each of them could work correctly yet when they are on concurrently with others, they sometimes malfunction. I'll fix it shortly.

## Aimbot

This is the feature I can guarantee the highest quality in the hacks I offer here.

Turning this function on automatically lets you aim at enemy's head with 100% precision.
It select the closest enemy from where your crosshair is as a target.

![aimbot](https://user-images.githubusercontent.com/33578715/89108283-b31e8d80-d469-11ea-8e55-e4e469d74576.gif)

## Glow hack

This feature allows you to see both opponents and teammate's outline through walls.

![Glow hack](https://user-images.githubusercontent.com/33578715/89087560-48b51100-d3c7-11ea-9ada-8ef04acfa52c.png)

## Trigger bot

Once you turn this on, you no longer have to press left click when you engage them.
This feature will complete the job for you.

- [ ] Fix a bug that keep shooting over hostile's head when you use Trigger bot in conjunction with Aimbot

## Anti recoil

This is basically a recoil control system.
It automatically calculate the in comming recoil and manipulate your angle to handle it.
But this doesn't guarantee the 100% accuracy.

![Anti recoil](https://user-images.githubusercontent.com/33578715/89087634-769a5580-d3c7-11ea-83b1-dc31345e7424.png)

# Contributors
- [l1m0n3](https://github.com/l1m0n3)

# Features being developed

**overall**
- [ ] Built-in pattern scanning system.
- [ ] Enemy's health indicator.
- [ ] Chams.
- [x] Place quit button on menu bar.
- [x] Aim bot.
- [x] Glow hack.
- [x] Trigger bot.
- [x] Neutralize recoil.
- [x] GUI menu for more better user experience (by hooking Directx9 endScene function).
- [x] Close GUI menu whenever user gets outta in game and goes back to main menu.
- [x] Save setting automatically that user inputs to toml file.
- [x] Add a "reset setting" button.

**Aimbot**
- [x] Fix a bug that causes crosshair to snap to the x and y axis of an enemy's head
- [x] Create an unawareness zone that doesn't affect to crosshair movement.
- [x] Check if bDormant is true
- [x] Aiming smoother rather than instantly stick crosshair to the target
- [x] Require more humanistic way to aim
- [x] Aim at closest enemy based on the position of crosshair not physical distance so that user can move their angle most of the time

**Glow hack**
- [x] want it to be capable of setting specific color of outline.