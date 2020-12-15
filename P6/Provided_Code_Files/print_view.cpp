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
    // for (int row = -1; row < mHeight+1; row++) {
    //     for (int col = -1; col < mWidth+1; col++) {
    //         if (row == -1 || row == mHeight || col == -1 || col == mWidth) {
    //             std::cout << '*';
    //         }
    //         else {
    //             std::cout << lines[row][col];
    //         }
    //     }
    //     std::cout << std::endl;
    // }
    std::string border = std::string(mWidth+2, '*');
    std::cout << border << std::endl;
    for (size_t i = 0; i < lines.size(); i++) {
        std::cout << "*" << lines[i] << "*" << std::endl;
    }
    std::cout << border << std::endl;
    return;
}
