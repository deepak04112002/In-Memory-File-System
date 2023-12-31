# FileSystem Simulation

This is a simple console-based file system simulation implemented in C++. It provides basic functionalities to interact with directories and files through a set of commands. Users can create directories, navigate through the file system, list directory contents, create and view files, move/copy files, and perform other file system operations.

## Table of Contents
1. [Introduction](#introduction)
2. [Usage](#usage)
3. [Commands](#commands)
4. [Improvements](#improvements)
5. [Instructions to Run](#instructions-to-run)
6. [Additional Information](#additional-information)

## Introduction

The file system simulation consists of three main classes: `File`, `Directory`, and `FileSystem`. 
- `File` represents a file with a name and content.
- `Directory` represents a directory with a name and contains maps of subdirectories and files.
- `FileSystem` is the main class that manages the file system operations.

## Usage

The program provides a command-line interface allowing users to interact with the simulated file system. It supports commands such as `mkdir`, `cd`, `ls`, `cat`, `touch`, `echo`, `mv`, `cp`, `rm`, and more.

## Commands

1. **mkdir \<directory_name\>**: Create a new directory.
2. **cd \<path\>**: Change the current directory.
3. **ls [\<path\>]**: List the contents of the current or specified directory.
4. **cat \<file_name\>**: Display the content of a file.
5. **touch \<file_name\>**: Create a new file.
6. **echo \<text\> > \<file_name\>**: Write text to a file.
7. **mv \<source_path\> \<destination_path\>**: Move a file or directory.
8. **cp \<source_path\> \<destination_path\>**: Copy a file or directory.
9. **rm \<path\>**: Remove a file or directory.
10. **exit**: Exit the file system simulation.

## Improvements

1. **Command-Line Interface:**
   - The program provides a simple and intuitive command-line interface, making it user-friendly.

2. **Error Handling:**
   - The program includes error handling to notify users about various issues, such as directory or file not found, failed operations, etc.

3. **Modularity:**
   - The code is modular, with separate classes for files, directories, and the file system. This makes it easy to understand and maintain.

## Instructions to Run

1. **Clone the Repository:**
   ```bash
   git clone <repository_url>
   cd filesystem-simulation
