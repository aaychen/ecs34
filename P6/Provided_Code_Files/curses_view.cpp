#include "curses_view.hpp"

/**
 * Side note: This class should probably be what is known as a singleton
 * class, i.e. a class that uses some setup (e.g. a static variable) to
 * prevent more than one instance of it from being created. I did not do this.
 */

CursesView::CursesView(int height, int width)
    : View(height, width)
{
    // TODO: Implement. Set up curses.
    initscr();
    cbreak();
    noecho();
    clear();
}

CursesView::~CursesView()
{
    // TODO: Implement. Clean up curses.
    endwin();
}

void CursesView::draw(const std::vector<std::string>& lines)
{
    // TODO: Implement.
    int row = 3;
    std::string border = std::string(mWidth+2, '*');
    mvaddstr(row, 0, border.c_str());
    for (size_t i = 0; i < lines.size(); i++) {
        row++;
        move(row, 0);
        addch('*');
        mvaddstr(row, 1, lines[i].c_str());
        move(row, lines[i].size() + 1);
        addch('*');
    }
    mvaddstr(row, 0, border.c_str());
    curs_set(0);
    refresh();
    return;
}
