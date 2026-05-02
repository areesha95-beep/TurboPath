#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;
namespace fs = std::filesystem;

// This is the index: filename, list of full paths
unordered_map<string, vector<string>> fileIndex;

//traverse the directory and build the index
void buildIndex(const string& rootPath) {

    fileIndex.clear(); // clearing the  old data if refreshing 

    if (!fs::exists(rootPath) || !fs::is_directory(rootPath)) {
        cout << "Invalid directory path." << endl;
        return;
    }

    // recursive_directory_iterator goes into all subfolders automatically
    for (const auto& entry : fs::recursive_directory_iterator(rootPath)) {
        if (fs::is_regular_file(entry.path())) {

            string filename = entry.path().filename().string(); 
            string fullPath = entry.path().string();          

            fileIndex[filename].push_back(fullPath); // store it in the map
        }
    }

    cout << "Indexing complete. " << fileIndex.size() << " unique filenames indexed." << endl;
}

//search the index by file name 
void searchFile(const string& query) {

    if (fileIndex.count(query)) {
        cout << "Found:" << endl;
        for (const string& path : fileIndex[query]) {
            cout << "  " << path << endl;
        }
        return;
    }

    vector<string> results;
    for (const auto& entry : fileIndex) {
        string nameWithoutExt = fs::path(entry.first).stem().string();
        if (nameWithoutExt == query) {
            for (const string& path : entry.second) {
                results.push_back(path);
            }
        }
    }

    if (!results.empty()) {
        cout << "Found:" << endl;
        for (const string& path : results) {
            cout << "  " << path << endl;
        }
    }
    else {
        cout << "File not found: " << query << endl;
    }
}

int main() {

    string rootPath;
    cout << "    TurboPath File Search    " << endl;
    cout << "Enter root directory path to index: ";
    getline(cin, rootPath);

    buildIndex(rootPath);

    cout << "\nCommands: search <filename>   ,  refresh  ,  exit" << endl;

    string input;
    while (true) {
        cout << "\n> ";
        getline(cin, input);

        if (input == "exit") {
            cout << "Goodbye!" << endl;
            break;
        }
        else if (input == "refresh") {
            buildIndex(rootPath);
        }
        else if (input.substr(0, 7) == "search ") {
            string query = input.substr(7); 
            searchFile(query);
        }
        else {
            cout << "Unknown command. Use: search <filename> , refresh , exit" << endl;
        }
    }

    return 0;
}