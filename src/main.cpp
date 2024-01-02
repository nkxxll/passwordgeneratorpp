#include <curses.h>
#include <ncurses.h>
#include <string>

#include <pwgenerator.h>

#define WIDTH 80
#define HEIGHT 10

using namespace std;

void cleanCurses(WINDOW *win)
{
    // deallocates memory and ends ncurses
    delwin(win);
    endwin();
}

int main(int argc, char **argv)
{
    // init screen and sets up screen
    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    // get the viewport width and height
    int termwidth  = getmaxx(stdscr);
    int termheight = getmaxy(stdscr);

    // make a new window
    WINDOW *win = newwin(HEIGHT, WIDTH, termheight / 2 - HEIGHT / 2,
                         termwidth / 2 - WIDTH / 2);
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
    int    max_chars_per_line = WIDTH - 2;

    while (text_pos < text.length())
    {
        string line = text.substr(text_pos, max_chars_per_line);
        mvwprintw(win, 1 + current_line, 1, "%s", line.c_str());
        text_pos += max_chars_per_line;
        current_line++;
    }
    wrefresh(win);

    Generator generator = Generator();

    bool choosing = true;

    // getchar
    while (choosing)
    {
        int ch = wgetch(win);
        switch (ch)
        {
            case '1':
                mvwprintw(win, 3, 1, "You chose alphabetic");
                generator.setCharset(Generator::ALPHABETIC);
                choosing = false;
                break;
            case '2':
                mvwprintw(win, 3, 1, "You chose alphanumeric");
                generator.setCharset(Generator::ALPHANUMERIC);
                choosing = false;
                break;
            case '3':
                mvwprintw(win, 3, 1, "You chose alphanumeric-symbolic");
                generator.setCharset(Generator::ALPHANUMERIC_WITH_SYMBOLS);
                choosing = false;
                break;
            default:
                mvwprintw(win, 3, 1, "You chose nothing");
                break;
        }
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
    max_chars_per_line = WIDTH - 2;

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
    wgetnstr(win, char_count, 2);

    // print out the result
    string pw = generator.generatePassword(atoi(char_count));
    mvwprintw(win, 2, 1, "Password: ");
    text_pos           = 0;
    current_line       = 2;
    int offset         = 10;
    max_chars_per_line = WIDTH - 2;
    while (text_pos < pw.length())
    {
        string line = pw.substr(text_pos, max_chars_per_line - offset);
        mvwprintw(win, current_line, 1 + offset, "%s", line.c_str());
        text_pos += max_chars_per_line - offset;
        offset      = 0;
        current_line++;
    }

    mvwprintw(win, current_line + 1, 1, "Press any key to exit...");
    wrefresh(win);

    // pause the screen output
    getch();

    // clean up
    cleanCurses(win);
    return 0;
}
