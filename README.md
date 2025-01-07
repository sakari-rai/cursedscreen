# Cursed Screen Animation

Non-interactive terminal demo application written in C++ using Curses (PDCurses on Windows). The program displays moving parts as triangles that bounce around the screen.

## Features

- Moving parts with random positions and velocities
- Triangles are rotated based on their velocity direction
- Uses ncurses for rendering

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- CMake
- ncurses library (PDCurses on Windows)

### Building

1. Clone the repository:
    ```sh
    git clone https://github.com/sakari-rai/cursedscreen.git
    cd cursedscreen 
    ```

2. Configure and Build the project:
    ```sh
    cmake -S . -B build
    cmake --build build
    ```

### Running

Run the program:
```sh
./build/cursed_screen
```

## Acknowledgements

This program was the product of testing the free Github Copilot VSCode integration. It was fun and amazing.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
