# Semester 2 Project
# Artillery Game Project

A turn-based artillery game with physics simulation, level progression, and persistent state saving.

## Architecture Overview

The game follows a component-based architecture with these core systems:

### 1. Game Engine Core
- **GameEngine**: Main controller managing the game loop and subsystems  
- **PhysicsEngine**: Handles projectile trajectories, wind effects, and collisions  
- **Level Manager**: Loads and tracks level progress with multiple targets  
- **StateManager**: Handles save/load functionality  
- **Logger**: Records game events for debugging  

### 2. Game Objects
- **Players**: Control angle/power and alternate turns  
- **Projectiles**: Simulated physics objects affected by wind/gravity  
- **Targets** (Static/Moving): Destructible objects with hit detection  
- **Obstacles** (Circular/Rectangular): Environment collision objects  

## Key Features

### Gameplay Flow
1. **Turn System**:
   - Players take alternating turns  
   - Adjustable angle (0-90°) and power (0-100%)  
   - Wind affects projectile trajectory  

2. **Level Progression**:
   - Multiple targets per level (must destroy all to advance)  
   - Environmental obstacles  
   - Progressive difficulty scaling  

3. **State Persistence**:
   - Save at any point (mid-level progress preserved)  
   - Auto-save on level completion  
   - Load previous game sessions  

### Physics Simulation
- Projectile motion with gravity (9.8 m/s²)  
- Wind force affecting trajectory  
- Collision detection

### Technical Specifications

| Component          | Implementation                              |
|--------------------|--------------------------------------------|
| Integration Method | Semi-Implicit Euler                        |
| Timestep           | Frame-rate independent (uses Δt)           |
| Coordinate System  | Right-handed (Y-up)                        |
| Units              | Meters, seconds, newtons                   |
| Error Handling     | Throws PhysicsException on invalid states  |

### Simulation Pipeline

1. **Initialization**  
   - Convert player angle/power to velocity vector  
2. **Per-Frame Update**  
   - Apply wind and gravity forces  
   - Update position using current velocity  
3. **Collision Phase**  
   - Check against targets/obstacles  
   - Resolve collisions if detected  

> **Note**: Wind effects are cumulative with gravity, creating realistic parabolic trajectories.
The physics engine uses realistic Newtonian mechanics to simulate projectile motion:

```cpp
// Core equation: F = ma (simplified to velocity changes)
velocity.x += wind.x * deltaTime;
velocity.y += (gravity + wind.y) * deltaTime;
position += velocity * deltaTime;
```
 ## 🎮 How to Play

### Basic Controls
```plaintext
[W/S]  : Increase/Decrease Launch Angle (0°-90°)
[A/D]  : Increase/Decrease Power (0%-100%)
[SPACE]: Fire Projectile
[ESC]  : Pause and Save Game
```
UML:
![UML](https://github.com/user-attachments/assets/fae6c29d-8774-4da3-be3b-7f00a442eb9c)
Flow Chart:
![FlowChart](https://github.com/user-attachments/assets/240e34a4-6085-485b-882f-0101d5531018)
