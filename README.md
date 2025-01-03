# Dear ImGui C++ Project

This project demonstrates how to integrate Dear ImGui with GLFW and OpenGL. It creates a simple window with Dear ImGui elements rendered using OpenGL.

## Project Structure

```
DearImGui-CPP/
├── Binaries/
├── Intermediates/
├── build/
├── src/
│   └── main.cpp
├── libs/
│   ├── glfw/ (fetched by CMake)
│   └── imgui/ (fetched by CMake)
├── vendor/
├── vs/
├── .gitignore
├── CMakeLists.txt
└── Scripts/Win-GenerateProject.bat & Scripts/GenreProject.sh
```

## Prerequisites

- CMake 3.10 or higher
- A C++20 compatible compiler
- OpenGL
- GLFW
- Dear ImGui

## Getting Started

### 1. Clone the Repository:
```bash
git clone https://github.com/NorthernL1ghts/DearImGui-CPP.git
cd DearImGui-CPP
```

### 2. Build the Project:
For Windows, run the batch file to generate and build the project:
```bash
Win-GenerateProject.bat
```

### 3. Run the Project:
After building the project, you can run the executable located in the Binaries directory:
```bash
./Binaries/DearImGui-CPP
```

## Project Details

- **CMakeLists.txt**: Configures the project, fetches dependencies (GLFW and ImGui), and sets up the build.
- **main.cpp**: The main source file that initializes GLFW, sets up Dear ImGui, and renders the ImGui interface.
- **.gitignore**: Specifies which files and directories to ignore in version control.

## Notes

- Ensure you have the necessary development libraries for OpenGL, GLFW, and Dear ImGui installed on your system.
- This project is configured to create Binaries and Intermediates directories for output files and intermediate build files, respectively.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.

## Acknowledgements

- [GLFW](https://www.glfw.org/)
- [Dear ImGui](https://github.com/ocornut/imgui)

Feel free to modify and expand this project to suit your needs!

