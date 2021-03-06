<div align="center">
    <img src="due.png">
</div>


# duedate
`duedate` is a simple CLI tool for tracking tasks and due dates written in C++11. A prototype of this project written in python is available at [fadedlamp42/py-duedate](https://github.com/fadedlamp42/py-duedate), which this project depreciates.

## Motivation
As a full-time student, I observed that a non-trivial amount of my time was spent remembering when my next assignments, quizzes, and exams were coming up. Keeping this information in working memory for long enough to reason about what I should be prioritizing was becoming nearly impossible to manage efficiently, hence [py-duedate](https://github.com/fadedlamp42/py-duedate) was born. I immediately saw a boost in productivity as I could finally focus on what I was doing instead of what I should be doing.

The core idea is simple: assignments and similar time-sensitive obligations require a level of foresight to complete well. This tool hopes to provide this foresight (and the performance boost associated with starting work early) without the mental overhead of remembering each obligation separately.

This iteration of the project was born out of a frustration with the slow execution inherent of a python script importing a data-processing library. I know that reducing dependencies and perhaps using caches or Cython cleverly could have alleviated this pain, but this frankly seemed more fun.

## Installation
Run `sudo make install` on any UNIX-based system.

## Usage
`due FILE [all | peek DAYS]`: running with no arguments first attempts to read the file specified by the `HW` environment variable, failing over to ~/hw.txt` for convenience of students.

[FILE] may be a relative or absolute path such as `../file.txt` or `/home/work/file.txt`.

The `all` argument displays all dates regardless of their range.

The `peek DAYS` argument shows all dates `DAYS` days into the future.

## Input file format
Input files are assumed to be plain text files with one line holding one due date. Fields are delimited by `|` (ASCII 124) and leading spaces are ignored.

Line format: `task name | {weekday} {month}/{day} | {days to complete}`

Weekday is expected to be the full, title-case name ("Monday", "Wednesday")

Year is currently assumed to be current year.

Example: `Chinese homework | Sunday 03/29 | 4` signifies a due date titled "Chinese homework" due on Sunday 03/29 that the user expects to work on for 4 days.

## Example (ran on Saturday 03/28)
Input: `due example.txt`

Output:
```
1 day until Chinese homework (4 needed)
3 days until Calculus homework (4 needed)
3 days until Biology test 10:30am (4 needed)
```

Notice that the final due date in `example.txt` is ignored because 03/28 is not within 2 days of 04/1.
