#include <ncurses.h>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int height = 10;
    int width  = 80;

    // init screen and sets up screen
    initscr();
    noecho();

    // make a new window
    WINDOW *win = newwin(height, width, 2, 5);
    refresh();

    // make a box around the window
    box(win, 0, 0);

    // give the window a title
    mvwprintw(win, 0, 1, "Password Generator");

    // ask for a character set in the box
    string text = "Choose a character set (alphabetic (1), alphanumeric (2) or "
                  "alphanumeric-symbolic (3)): ";
    int    text_pos           = 0;
    int    current_line       = 0;
    int    max_chars_per_line = width - 2;
    while (text_pos < text.length())
    {
        string line = text.substr(text_pos, max_chars_per_line);
        mvwprintw(win, 1 + current_line, 1, "%s", line.c_str());
        text_pos += max_chars_per_line;
        current_line++;
    }
    wrefresh(win);

    // getchar
    int ch = getch();
    switch (ch)
    {
        case '1':
            mvwprintw(win, 3, 1, "You chose alphabetic");
            break;
        case '2':
            mvwprintw(win, 3, 1, "You chose alphanumeric");
            break;
        case '3':
            mvwprintw(win, 3, 1, "You chose alphanumeric-symbolic");
            break;
        default:
            mvwprintw(win, 3, 1, "You chose nothing");
            break;
    }
    wrefresh(win);

    // pause the screen output
    getch();

    // deallocates memory and ends ncurses
    delwin(win);
    endwin();
    return 0;
}
