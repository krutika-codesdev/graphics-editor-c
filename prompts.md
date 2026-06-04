# Workflow

## Tools Used

* VS Code: coding and testing
* GCC: compilation
* Git/GitHub: version control
* Antigravity: code review, design guidance, architecture discussion, prompt-driven development

## Development Process

1. Create or update feature locally.
2. Test using GCC.
3. Review design and implementation with Antigravity.
4. Refine code based on feedback.
5. Commit changes.
6. Push to GitHub.

# Project History (Before Antigravity)

* Created GitHub repository.
* Connected local project to GitHub.
* Created initial project structure.
* Implemented initializeScreen().
* Implemented displayScreen().
* Implemented drawHorizontalLine().
* Implemented drawVerticalLine().
* Tested coordinate system and rendering.
* Committed and pushed progress to GitHub.

# Antigravity Prompt Log

## 2026-06-04

### Goal
Review the current progress of the C-based terminal graphics editor and suggest the next milestone.

### Prompt
"I am building a C-based terminal graphics editor.

Current implementation:
- 2D character array canvas
- initializeScreen()
- displayScreen()
- drawHorizontalLine()
- drawVerticalLine()

GitHub repository already exists.

Assignment requirements:
- rectangle
- triangle
- circle
- add objects
- delete objects
- modify objects

Review my current progress and suggest the next milestone."

### Response Summary
Antigravity analyzed the current implementation in main.c and recommended shifting from drawing directly onto the 2D grid to a Vector/Scene Graph data model (an array of Shape structs) to support the "add, delete, and modify objects" requirements. Suggested milestones included:
1. Data Model & Render Pipeline Setup
2. Shape Drawing Algorithms (Rectangle, Triangle, Circle)
3. Interactive CLI for Object Management

### Action Taken
Acknowledged the recommended architecture, but decided to complete the basic drawing primitives first before refactoring the data model.

---

## 2026-06-04

### Goal
Design a `drawRectangle()` function using the existing horizontal and vertical line functions.

### Prompt
"I understand the long-term architecture recommendation.

Before introducing shape structs and object management, I want to complete the basic drawing primitives.

Please help me design drawRectangle() using my existing horizontal and vertical line functions.

Explain the reasoning and coordinate calculations without redesigning the entire project yet."

### Response Summary
Calculated the coordinates for the top, bottom, left, and right borders based on an anchor point $(x, y)$, width $w$, and height $h$, resulting in $x_2 = x + w - 1$ and $y_2 = y + h - 1$. Mapped these edges to the existing drawHorizontalLine() and drawVerticalLine() functions. Warned about corner-overwrite behavior depending on the order of execution.

### Action Taken
Implemented drawRectangle() using the provided coordinate calculations and tested different border rendering orders to evaluate corner appearance.

---

## 2026-06-04

### Goal
Analyze the visual consequences of reversing the drawing order in `drawRectangle()` to draw vertical lines first and horizontal lines last.

### Prompt
"I currently draw my rectangle by drawing horizontal lines first and vertical lines second.

This produces corners like:

|______________|
|..............|
|..............|
|______________|

I am considering reversing the drawing order so that vertical lines are drawn first and horizontal lines are drawn last.

Analyze how the visual output will change.

Explain which characters will overwrite the corners, what the resulting rectangle will look like, and whether this improves readability in a terminal-based graphics editor.

Do not rewrite the entire program. Focus only on the rendering consequences of changing the drawing order."

### Response Summary
Explained that drawing horizontal lines last causes the corner coordinates to be overwritten by the underscore (`_`) character. This results in a "floating lid" effect that leaves the top corners visually disconnected/open. Recommended keeping vertical lines drawn last to keep the shape enclosed, and suggested using a hyphen `-` for horizontal lines and `+` for corners for standard ASCII box-drawing.

### Action Taken
Tested both rendering orders and chose to draw vertical borders first and horizontal borders last because the top and bottom borders appeared visually cleaner in the terminal output.

---

## 2026-06-04

### Goal
Design and implement a general drawLine() function using the DDA algorithm.

### Prompt
"I have completed:

* initializeScreen()
* displayScreen()
* drawHorizontalLine()
* drawVerticalLine()
* drawRectangle()

I now realize that the assignment requires a general line-drawing capability, not just horizontal and vertical lines.

Before implementing drawTriangle(), I want to design and implement a general drawLine() function that can draw lines between any two points on my character canvas.

Current canvas details:

* WIDTH = 50
* HEIGHT = 35
* Coordinates are stored as screen[y][x]
* The canvas is a 2D character array

Please help me think through the implementation.

Focus on:

1. The coordinate reasoning behind drawing a line between arbitrary points.
2. How DDA would work step-by-step on a character grid.
3. Why DDA may be a good choice for a beginner project compared to Bresenham's algorithm.
4. How drawLine() could later be reused by drawTriangle() and other shapes.

Do not generate the final complete code immediately.

Instead:

* Explain the algorithm.
* Break implementation into small steps.
* Suggest simple tests I can run after each step.
* Help me understand the design decisions before coding."

### Response Summary
Antigravity explained the DDA line-drawing algorithm, including dx, dy, steps, x_inc, and y_inc calculations. It demonstrated coordinate generation for a sample line and recommended implementing the algorithm incrementally with debugging and testing at each stage. It also explained how drawLine() could later be reused for triangles and other polygonal shapes.

### Action Taken
Implemented DDA setup and tested the calculations using the line from (0,0) to (4,2). Verified:
* dx = 4
* dy = 2
* steps = 4
* x_inc = 1.0
* y_inc = 0.5

Generated and verified the coordinate sequence:
(0,0)
(1,1)
(2,1)
(3,2)
(4,2)

Replaced coordinate debugging output with pixel plotting and successfully rendered the line on the canvas using '*' characters.

---

## 2026-06-04

### Goal
Design and implement drawTriangle() using the existing DDA-based drawLine() function.

### Prompt
"I have completed:

* initializeScreen()
* displayScreen()
* drawHorizontalLine()
* drawVerticalLine()
* drawRectangle()
* drawLine() using the DDA algorithm

I want to implement drawTriangle() next.

Since I already have a general drawLine() function, explain how to represent a triangle using three vertices and how drawTriangle() can reuse drawLine().

Focus on geometry, coordinate representation, testing strategy, and function design before generating code."

### Response Summary
Antigravity explained that a triangle can be represented by three vertices:
P1(x1, y1), P2(x2, y2), and P3(x3, y3).

It recommended implementing drawTriangle() by reusing drawLine() three times:
* P1 to P2
* P2 to P3
* P3 to P1

It also suggested three testing scenarios:
* Axis-aligned right triangle
* Arbitrary acute triangle
* Boundary clipping test

### Action Taken
Implemented drawTriangle() using three drawLine() calls.

Tested using two configurations:

1. Axis-aligned right triangle
   P1(10,10)
   P2(25,10)
   P3(10,25)

2. Arbitrary acute triangle
   P1(25,5)
   P2(10,25)
   P3(40,20)

Verified:
- Horizontal, vertical, and diagonal edges render correctly.
- Vertices connect cleanly.
- Arbitrary slopes render without visible gaps.


# Project Progress

* [x] Canvas initialization
* [x] Screen rendering
* [x] Horizontal line
* [x] Vertical line
* [x] Rectangle
* [x] Line
* [x] Triangle
* [ ] Circle
* [ ] Add object
* [ ] Delete object
* [ ] Modify object

# Maintenance Instructions

Future Antigravity interactions should be appended to the Prompt Log using the same structure and formatting:
```markdown
## Date

### Goal

### Prompt

### Response Summary

### Action Taken

### Commit (optional)
```
Do not replace or overwrite existing entries in the Prompt Log; always append new interactions chronologically.