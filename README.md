# Invaders
Old invaders game prototype that runs in terminal using the ncurses library.

## Compiling:
1. Make sure you have installed ncurses/libncurses on your system:

- ### on Debian/Ubuntu:
  - `sudo apt-get install libncurses5-dev libncursesw5-dev` 

- ### on Fedora 21 or older/CentOS/RedHat:
  - `sudo yum install ncurses-devel`

2. Compile with gcc or other c compiler using the -lncurses flag: 
- `gcc -o <filename> invaders.c -lncurses`
