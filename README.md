# Terminal Graphics Editor in C

A lightweight, console-based 2D vector graphics editor implemented in C. The application allows users to create, view, modify, and delete geometric shapes dynamically on a 50x35 character grid using a command-line menu interface.

## Features

* **Interactive Menu Interface:** A robust CLI menu for object management.
* **Canvas Initialization & Rendering:** Wipes and redraws the screen from a stored list of shapes to prevent overlapping drawing artifacts.
* **Shape Listing:** View active shapes with their unique IDs and current coordinates.
* **Object Operations:**
  * **Add Objects:** Lines, Rectangles, Triangles, and Circles.
  * **Modify Objects:** Shape-specific coordinate updates by ID.
  * **Delete Objects:** Soft deletion by ID to keep the scene array indices consistent.
* **General Line Drawing:** Draws horizontal, vertical, and diagonal lines at any angle.
* **Boundary-Safe:** Fully clips shape coordinates extending outside the 50x35 screen dimensions.

## Algorithms Used

1. **DDA (Digital Differential Analyzer) Line Algorithm:** Used for drawing lines of arbitrary slopes in `drawLine()`.
2. **Midpoint Circle Algorithm:** Used for plotting smooth circle outlines efficiently with integer-only arithmetic in `drawCircle()`.
3. **8-Way Symmetry:** Reuses single-octant calculations to plot circles dynamically in `plotCirclePoints()`.

## Coordinate System

* **Canvas Size:** 50 Columns (Width) x 35 Rows (Height)
* **Origin (0,0):** Located at the **top-left** corner of the screen.
* **Indexing:** Stored internally as `screen[y][x]` to map to standard terminal rows and columns.

## Repository Structure

* `main.c`: Contains all drawing routines, scene management operations, and the user menu loop.
* `prompts.md`: Contains the detailed prompt-driven development history, project milestones, and action logs.
* `README.md`: Project summary, setup, and execution instructions.

## Prerequisites

* A standard C compiler (e.g., GCC/MinGW)
* Standard C libraries (`stdio.h`, `stdlib.h`, `math.h`)

## Compilation and Execution

To compile and run the application, use any standard terminal:

1. **Compile the source code:**

```bash
gcc main.c -o main
```

If your compiler reports unresolved math library symbols, compile with:

```bash
gcc main.c -o main -lm
```

*(Note: The `-lm` flag links the math library which is required for circle and line rounding operations on some systems.)*

2. **Execute the program:**

```powershell
.\main.exe
```