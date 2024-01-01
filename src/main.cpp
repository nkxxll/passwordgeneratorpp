#include <curses.h>
#include <ncurses.h>
#include <string>

#include <pwgenerator.h>

using namespace std;

int main(int argc, char **argv)
{
    int height = 10;
    int width  = 80;

    // init screen and sets up screen
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

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
    size_t text_pos           = 0;
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

    // stop here
    getch();

    // clear the window
    werase(win);

    box(win, 0, 0);
    
    // give the window a title
    mvwprintw(win, 0, 1, "Password Generator");

    // ask for a character set in the box
    text_pos           = 0;
    current_line       = 0;
    max_chars_per_line = width - 2;
    
    text = "How many characters do you want: ";

    while (text_pos < text.length())
    {
        string line = text.substr(text_pos, max_chars_per_line);
        mvwprintw(win, 1 + current_line, 1, "%s", line.c_str());
        text_pos += max_chars_per_line;
        current_line++;
    }
    wrefresh(win);

    char char_count[6];
    wgetnstr(win, char_count, 5);

    // print out the result
    mvwprintw(win, 3, 1, "You chose %s characters", char_count);
    wrefresh(win);

    // pause the screen output
    getch();

    // deallocates memory and ends ncurses
    delwin(win);
    endwin();
    return 0;
}
