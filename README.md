
# WIP!

## The WOMP Editor -> What is it?

Womp editor is a personal project of mine, and is **NOT** yet fully functional **OR** safe. It does not even support opening or closing files!!

Current implementation is built using *[ncurses][1]* and supports a customizable load in screen using *[figlet][2]* (change the EDITOR_NAME macro, limited to 25 chars).


I fully plan to make this fully functional and _(perhaps)_ use it personally. I want the womp editor to have a personal touch, and to be littered with easter eggs and chance encounters to lightens one day programming in the terminal :) .

## Using The Womp Editor

Run using `make`. If compiling make sure to link ncurses: 
`gcc -o text-editor main.c -lncurses`. 

### Dependencies:

The current pre-release version requires it to be compiled. As this is a *terminal based* text editor, **you are expected to be familiar with working in the terminal**.

- ncurses
	- Most UNIX based systems come with ncurses by default, but [this article][3] outlines the installation on most linux based systems. 
- figlet
	- Figlet is an optional dependency, but enables the use of ASCII art to replace the default text splash screen (the splash screen is also optional!). Linux based install guide can be found [here][4]
- gcc
	- The WOMP editor is written in C, and must be compiled before use! Thus you will require a C compiler.  I suggest [GCC][5].

## Want to contribute?

The current priority is to make The Womp Editor functional, but (more importantly), **SAFE**. File opening and writing will **ONLY** be implemented once there is a great deal of confidence in the editor not destroying files!

Beyond that the womp editor should be light hearted and easily customisable. Ideas such as custom holiday startup art and messages, regex detecting common programmer typo's (such as fi in a language where fi is not a key word) and the occasional classical cipher event should be the true nature of the editor as it approaches completion.



[1]: https://en.wikipedia.org/wiki/Ncurses#:~:text=ncurses%20(new%20curses)%20is%20a,in%20a%20terminal%2Dindependent%20manner.
[2]: http://www.figlet.org/
[3]: https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/
[4]: https://pq.hosting/en/help/instructions/570-komanda-figlet-v-linux.html
[5]: https://gcc.gnu.org/install/
