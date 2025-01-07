# Cursed Screen Animation

This project is a fun animation program written in C++ using the ncurses library. The program displays moving parts as triangles that bounce around the screen.

## Features

- Moving parts with random positions and velocities
- Triangles are rotated based on their velocity direction
- Uses ncurses for rendering

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- ncurses library

### Building

1. Clone the repository:
    ```sh
    git clone https://github.com/YOUR_GITHUB_USERNAME/YOUR_REPOSITORY_NAME.git
    cd YOUR_REPOSITORY_NAME
    ```

2. Build the project:
    ```sh
    g++ -o cursed_screen main.cpp AppState.cpp FrameBuffer.cpp -lncurses
    ```

### Running

Run the program:
```sh
./cursed_screen
```

## Acknowledgements

This program was written with the help of GitHub Copilot.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
