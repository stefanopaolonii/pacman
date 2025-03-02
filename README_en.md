# Pac-Man Project for LandTiger Board

This repository contains the implementation of the Pac-Man game for the LandTiger board, developed as part of the course **"Computer Systems Architecture"**.

⚠️ **Warning**: This project was developed **exclusively for educational purposes** and **should not be used as a template for the exam**. There are some **modifications in the libraries used**.

## Project Overview

The project implements a Pac-Man game on the LandTiger board, with the following features:

- A maze with pills to collect
- Score tracking
- AI-controlled ghost
- Sound effects
- CAN communication

## Project Requirements

### Extra Points Specifications #1

#### Maze and Pills:

- The maze must contain exactly 240 Standard Pills.
- 6 Power Pills placed in random positions that replace the Standard Pills.
- Power Pills appear randomly both in position and time.

#### Player Movement:

- Control Pac-Man using a joystick (left, right, up, down).
- Pac-Man continues to move in the selected direction until:
    - The player selects a new direction.
    - Pac-Man encounters a wall (stops and waits for input).

#### Teleportation:

- When Pac-Man reaches the central teleportation positions, he exits from one side and re-enters from the other.
- The direction of movement is maintained during teleportation.

#### Scoring System:

- Standard Pills: +10 points.
- Power Pills: +50 points.
- Every 1000 points awards an extra life (starting with 1 life).

#### Game Controls:

- **INT0**: Pause/Resume the game. In pause mode, a "PAUSE" message appears in the center of the screen.
- The game starts in "PAUSE" mode.

#### Game Timer and End Conditions:

- The countdown starts from 60 seconds.
- The victory screen appears when all pills are collected.
- The **Game Over** screen appears if the countdown timer reaches 0.

### Extra Points Specifications #2

#### AI-Controlled Ghost (Blinky):

- Implements two AI strategies:
    - **Chase Mode**: Actively chases Pac-Man using pathfinding algorithms (A* algorithm).
    - **Frightened Mode**: Activated when Pac-Man eats a Power Pill.
        - The ghost turns blue for 10 seconds, flees from Pac-Man, and can be eaten by Pac-Man for an additional 100 points.
        - Reappears after 3 seconds at the central spawn point.

#### Sound Effects:

- Speaker configured to play sound effects and background music.

#### CAN Communication:

- Uses the CAN peripheral to transmit the game state.
- Implemented in external "loopback" mode using CAN1 (transmitter) and CAN2 (receiver).
- **Message format** (32-bit unsigned int): 
    - Copy | Remaining time (8 bits) | Remaining lives (8 bits) | Score (16 bits)

## Hardware Requirements

- LandTiger board with LPC1768 microcontroller.
- Display to show the maze and game state.
- Joystick to control Pac-Man.
- Speaker for sound effects.
- INT0 button for pause functionality.
