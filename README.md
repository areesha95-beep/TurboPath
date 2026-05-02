# TurboPath
TurboPath — Fast File Search

SETUP (Visual Studio 2022)
  1. Open TurboPath.sln
  2. Set C++ standard to C++17
     Project Properties > C/C++ > Language > C++ Language Standard
  3. Ctrl + F5 to build and run

USAGE
  When prompted, enter a folder path to index:
    e.g. D:\areesha
    e.g. C:\Users\YourName\Documents

  Once indexed, use these commands:

    search <filename>   find a file by name (extension optional)
                          search report.pdf
                          search report

    refresh             rescan the folder for new/changed files

    exit                quit

NOTES
  Multiple files with the same name? All paths will be listed.
  Search runs in O(1) average time via hash map.
