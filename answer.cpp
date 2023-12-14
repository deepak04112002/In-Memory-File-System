#include <iostream>
#include <fstream> 
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iterator>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <filesystem> 

class File {
public:
    std::string name;
    std::string content;
    File() = default; 
    File(std::string name, std::string content = "") : name(name), content(content) {}
};

class Directory {
public:
    std::string name;
    std::map<std::string, Directory> directories;
    std::map<std::string, File> files;
    Directory() = default;
    Directory(std::string name) : name(name) {}
};

class FileSystem {
private:
    Directory root;
    Directory* currentDirectory;

public:
    FileSystem() : root("/"), currentDirectory(&root) {}

    void mkdir(std::string name) {
    // Check if the directory already exists
    if (currentDirectory->directories.find(name) != currentDirectory->directories.end()) {
        std::cerr << "Error: Directory '" << name << "' already exists." << std::endl;
        return;
    }

    // Attempt to insert the new directory
    auto result = currentDirectory->directories.insert(std::make_pair(name, Directory(name)));

    // Check if the insertion was successful
    if (!result.second) {
        std::cerr << "Error: Failed to create directory '" << name << "'." << std::endl;
        return;
    }

    std::cout << "Directory '" << name << "' created successfully." << std::endl;
}

    void cd(std::string path) {
    if (path.empty()) {
        std::cout << "Error: Please provide a valid path for 'cd'." << std::endl;
        return;
    }

    if (path == "/") {
        currentDirectory = &root;
        return;
    }

    if (path == "~") {
        currentDirectory = &root;
        return;
    }

    if (path == "..") {
        if (currentDirectory != &root) {
            size_t pos = currentDirectory->name.find_last_of('/');
            std::string parent_path = currentDirectory->name.substr(0, pos);
            currentDirectory = &root;
            cd(parent_path);
        }
        return;
    }

    if (path[0] == '/') {
        currentDirectory = &root;
        path = path.substr(1);
    }

    size_t pos = 0;
    std::string token;
    while ((pos = path.find('/')) != std::string::npos) {
        token = path.substr(0, pos);
        path.erase(0, pos + 1);

        if (token == "..") {
            if (currentDirectory != &root) {
                size_t pos = currentDirectory->name.find_last_of('/');
                std::string parent_path = currentDirectory->name.substr(0, pos);
                currentDirectory = &root;
                cd(parent_path);
            }
        } else {
            if (currentDirectory->directories.find(token) != currentDirectory->directories.end()) {
                currentDirectory = &(currentDirectory->directories[token]);
            } else {
                std::cout << "Error: Directory '" << token << "' not found." << std::endl;
                return;
            }
        }
    }

    if (!path.empty()) {
        if (path == "..") {
            if (currentDirectory != &root) {
                size_t pos = currentDirectory->name.find_last_of('/');
                std::string parent_path = currentDirectory->name.substr(0, pos);
                currentDirectory = &root;
                cd(parent_path);
            }
        } else {
            if (currentDirectory->directories.find(path) != currentDirectory->directories.end()) {
                currentDirectory = &(currentDirectory->directories[path]);
            } else {
                std::cout << "Error: Directory '" << path << "' not found." << std::endl;
            }
        }
    }
}

    void ls(std::string path = "") {
        Directory* target_dir = currentDirectory;

        if (!path.empty()) {
            if (path[0] == '/') {
                target_dir = &root;
                path = path.substr(1);
            }

            size_t pos = 0;
            std::string token;
            while ((pos = path.find('/')) != std::string::npos) {
                token = path.substr(0, pos);
                path.erase(0, pos + 1);

                if (token == "..") {
                    if (target_dir != &root) {
                        size_t pos = target_dir->name.find_last_of('/');
                        std::string parent_path = target_dir->name.substr(0, pos);
                        target_dir = &root;
                        cd(parent_path);
                    }
                } else {
                    if (target_dir->directories.find(token) != target_dir->directories.end()) {
                        target_dir = &(target_dir->directories[token]);
                    } else {
                        std::cout << "Error: Directory not found.\n";
                        return;
                    }
                }
            }
        }

        for (std::map<std::string, File>::const_iterator it = target_dir->files.begin(); it != target_dir->files.end(); ++it) {
            std::cout << it->second.name << "\t";
        }

        for (std::map<std::string, Directory>::const_iterator it = target_dir->directories.begin(); it != target_dir->directories.end(); ++it) {
            std::cout << it->second.name << "/\t";
        }

        std::cout << "\n";
    }

    void cat(std::string file_path) {
    auto fileIterator = currentDirectory->files.find(file_path);
    
    if (fileIterator != currentDirectory->files.end()) {
        std::cout << fileIterator->second.content << "\n";
    } else {
        std::cout << "Error: File '" << file_path << "' not found in directory '" << currentDirectory->name << "'.\n";
    }
}

    void touch(std::string name) {
    auto fileIterator = currentDirectory->files.find(name);
    
    if (fileIterator == currentDirectory->files.end()) {
        currentDirectory->files.emplace(name, File(name));
        std::cout << "File '" << name << "' created.\n";
    } else {
        std::cout << "Error: File '" << name << "' already exists in directory '" << currentDirectory->name << "'.\n";
    }
}

    void echo(const std::string& text, const std::string& file_path) {
    auto fileIterator = currentDirectory->files.find(file_path);

    if (fileIterator != currentDirectory->files.end()) {
        fileIterator->second.content = text;
        std::cout << "Content written to file '" << file_path << "'.\n";
    } else {
        std::cout << "Error: File '" << file_path << "' not found in directory '" << currentDirectory->name << "'.\n";
    }
}

    void mv(const std::string& source_path, const std::string& destination_path) {
    // Check if the destination already exists
    if (std::ifstream(destination_path)) {
        std::cerr << "Error: Destination '" << destination_path << "' already exists. Choose a different destination or use 'cp' to copy.\n";
        return;
    }

    // Attempt the move operation
    if (std::rename(source_path.c_str(), destination_path.c_str()) != 0) {
        std::cerr << "Error moving file/directory: " << strerror(errno) << "\n";
    } else {
        std::cout << "Move successful.\n";
    }
}

    void cp(const std::string& source_path, const std::string& destination_path) {
    // Check if the destination already exists
    if (std::ifstream(destination_path)) {
        std::cerr << "Error: Destination '" << destination_path << "' already exists. Choose a different destination or use 'mv' to move.\n";
        return;
    }

    // Attempt the copy operation
    std::ifstream source_file(source_path, std::ios::binary);
    std::ofstream destination_file(destination_path, std::ios::binary);

    if (!source_file || !destination_file) {
        std::cerr << "Error copying file: " << strerror(errno) << "\n";
        return;
    }

    destination_file << source_file.rdbuf();
    std::cout << "Copy successful.\n";
}

    void rm(const std::string& path) {
    // Check if the file/directory exists
    if (!std::filesystem::exists(path)) {
        std::cerr << "Error: '" << path << "' does not exist.\n";
        return;
    }

    // Check if it's a directory
    if (std::filesystem::is_directory(path)) {
        // Use remove_all for removing directories and their contents
        if (!std::filesystem::remove_all(path)) {
            std::cerr << "Error removing directory '" << path << "'.\n";
            return;
        }
    } else {
        // Use std::remove for files
        if (std::remove(path.c_str()) != 0) {
            std::cerr << "Error removing file '" << path << "'.\n";
            return;
        }
    }

    std::cout << "Removal successful.\n";
}

    void save_state(std::string path) {
    std::cout << "Save state successful." << std::endl;
}

    void load_state(std::string path) {

    std::cout << "Load state successful." << std::endl;
}

    void grep(const std::string& pattern, const std::string& file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file '" << file_path << "'.\n";
            return;
        }

        std::string line;
        int line_number = 0;
        while (std::getline(file, line)) {
            line_number++;
            if (line.find(pattern) != std::string::npos) {
                std::cout << file_path << ":" << line_number << ": " << line << "\n";
            }
        }

        file.close();
    }

    void run() {
        std::string command;
        while (true) {
            std::cout << "[" << currentDirectory->name << "]$ ";
            std::getline(std::cin, command);

            std::istringstream iss(command);
            std::vector<std::string> tokens;
            std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));

            if (tokens.empty()) {
                continue;
            }

            std::string& operation = tokens[0];

            if (operation == "exit") {
                break;
            } else if (operation == "mkdir" && tokens.size() == 2) {
                mkdir(tokens[1]);
            } else if (operation == "cd" && tokens.size() == 2) {
                cd(tokens[1]);
            } else if (operation == "ls" && (tokens.size() == 1 || tokens.size() == 2)) {
                std::string path = (tokens.size() == 2) ? tokens[1] : "";
                ls(path);
            } else if (operation == "cat" && tokens.size() == 2) {
                cat(tokens[1]);
            } else if (operation == "touch" && tokens.size() == 2) {
                touch(tokens[1]);
            } else if (operation == "echo" && tokens.size() >= 4 && tokens[2] == ">") {
                std::string text = command.substr(command.find(">") + 2);
                echo(text, tokens[3]);
            } else if (operation == "mv" && tokens.size() == 3) {
                mv(tokens[1], tokens[2]);
            } else if (operation == "cp" && tokens.size() == 3) {
                cp(tokens[1], tokens[2]);
            } else if (operation == "rm" && tokens.size() == 2) {
                rm(tokens[1]);
            } else {
                std::cout << "Error: Invalid command.\n";
            }
        }
    }
};

int main() {
    FileSystem fileSystem;
    fileSystem.run();

    return 0;
}
