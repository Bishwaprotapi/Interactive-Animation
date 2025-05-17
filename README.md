# Interactive Animation Project

## Overview
This project is an interactive animation system built using OpenGL and GLUT, featuring multiple animated scenes and day/night mode functionality. The project demonstrates various computer graphics techniques and interactive elements.

## Features

### Scene Controls
1. Press 1: Rain scene with animated raindrops and splash effects
2. Press 2: Two men wacking with animated arms
3. Press 3: Three birds flying with animated wings
4. Press 4: Four cows eating with animated mouths
5. Press 5: Five people walking home
6. Press 6: Six fish swimming with animated tails
7. Press 7: Seven butterflies flying with animated wings
8. Press 8: Eight cars moving with rotating wheels
9. Press 9: Nine stars twinkling with varying brightness

### Letter Controls
- Press A: Airplane flying across the sky
- Press E: Elephant walking with animated trunk
- Press I: Ice skater spinning and moving
- Press O: Ocean waves moving with varying amplitude
- Press U: Umbrella moving and opening/closing
- Press R: Robot dancing with animated parts

### Day/Night Mode
- Press D: Switch to day mode
- Press N: Switch to night mode

### Additional Controls
- Press M: Toggle animation on/off

## Technical Requirements

### Dependencies
- OpenGL
- GLUT (OpenGL Utility Toolkit)
- C++ Compiler (supporting C++11 or later)

### Installation

#### Windows
1. Install MinGW or Visual Studio
2. Install GLUT:
   - Download freeglut
   - Place `freeglut.dll` in `C:\Windows\System32`
   - Place `freeglut.lib` in your compiler's lib directory
   - Place `freeglut.h` in your compiler's include directory

#### Linux
```bash
sudo apt-get install freeglut3-dev
```

#### macOS
```bash
brew install freeglut
```

## Project Structure
```
project/
├── main.cpp          # Main source file
├── README.md         # This file
├── report.md         # Detailed project report
└── screenshots/      # Project screenshots
    ├── day_mode.png
    ├── night_mode.png
    ├── rain_scene.png
    ├── birds_scene.png
    └── robot_scene.png
```

## Screenshots

### Day Mode
![Day Mode](screenshots/day_mode.png)
- Bright blue sky
- Yellow sun
- Bright green ground
- White clouds

### Night Mode
![Night Mode](screenshots/night_mode.png)
- Dark blue sky
- White moon
- Dark green ground
- Twinkling stars

### Rain Scene
![Rain Scene](screenshots/rain_scene.png)
- Animated raindrops
- Splash effects
- Cloudy background

### Birds Scene
![Birds Scene](screenshots/birds_scene.png)
- Flying birds
- Animated wings
- Sky background

### Robot Scene
![Robot Scene](screenshots/robot_scene.png)
- Dancing robot
- Animated arms and legs
- Interactive movement

## Development
- OpenGL for graphics rendering
- GLUT for window management and user input
- C++ for core functionality

## Future Improvements
1. Add more interactive scenes
2. Implement 3D graphics
3. Add sound effects
4. Enhance visual effects
5. Add more user controls

## License
This project is open source and available for educational purposes.

## Author
[Your Name]

## Acknowledgments
- OpenGL community
- GLUT developers
- Computer Graphics course materials 