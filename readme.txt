CONTENTS
--------

1. Introduction
2. Requirements
3. Installation
4. Configuration

1. Introduction
---------------

    Puissance 4 uses the C language for its interface as well as its artificial intelligences.
    This module is compiled with the clang library and was designed for Ubuntu usage.

2. Requirements
---------------

This module requires the following libraries:

    1. clang(APT-Sources: http://archive.ubuntu.com/ubuntu focal/universe amd64 Packages)

3. Installation
---------------

    1. If not installed, install clang in the terminal emulator by typing: sudo apt install clang -y
    2. Change your current working directory to puissance4 and type: make
    3. If the puissance4 directory isn't added to your PATH variable, while keeping the same current working directory, type: ./puissance4

4. Configuration
----------------

    After ./puissance4, you need to type some arguments.
    First, the player's name or first AI's name.
    Second, the player's name or second AI's name.
    You can only put one human player by game, but you can put two AIs.
    Third, you can optionally put a number of games that will play automatically.
    
