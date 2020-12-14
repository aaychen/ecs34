#include "print_view.hpp"

#include <iostream>

/**
 * The constructor and destructor shouldn't need anything added.
 */

PrintView::PrintView(int height, int width)
    : View(height, width)
{
}

PrintView::~PrintView()
{
}

void PrintView::draw(const std::vector<std::string>& lines)
{
    // TODO: Implement.
    // lines is everything inside asterisks border
    for (int row = 0; row < mHeight + 2; row++) {
        for (int col = 0; col < mWidth + 2; col++) {
            if (row == 0 || row == mHeight + 1 || col == 0 || col == mWidth + 1) {
                std::cout << "*";
            }
            else {
                std::cout << "~";
            }
        }
        std::cout << std::endl;
    }
}
