# FileSystem Simulation

This is a simple console-based file system simulation implemented in C++. It provides basic functionalities to interact with directories and files through a set of commands. Users can create directories, navigate through the file system, list directory contents, create and view files, move/copy files, and perform other file system operations.

## Table of Contents
1. [Introduction](#introduction)
2. [Usage](#usage)
3. [Commands](#commands)
4. [Example Usage](#example-usage)
5. [Dependencies](#dependencies)
6. [Build and Run](#build-and-run)
7. [Contributing](#contributing)
8. [License](#license)

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

## Example Usage

```bash
$ mkdir Documents
$ cd Documents
$ touch notes.txt
$ echo "Important information" > notes.txt
$ ls
notes.txt
$ cat notes.txt
Important information
$ cd ..
$ ls
Documents/
$ rm Documents
$ ls
$ exit
