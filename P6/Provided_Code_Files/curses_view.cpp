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

}

CursesView::~CursesView()
{
    // TODO: Implement. Clean up curses.

}

void CursesView::draw(const std::vector<std::string>& lines)
{
   // TODO: Implement.

}
