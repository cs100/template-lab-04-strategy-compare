#ifndef __SPREADSHEET_HPP__
#define __SPREADSHEET_HPP__

class Compare;
class Select;

class Spreadsheet
{
    std::vector<std::vector<std::string> > data;
    Compare* compare = 0;
    Select* select = 0;

public:
    /* Constructors */
    Container() : sort_function(nullptr) { };
    Container(Sort* function) : sort_function(function) { };

    const std::string& cell_data(int row, int column) const
    {
        return data[row][column];
    }

    std::string& cell_data(int row, int column)
    {
        return data[row][column];
    }

    void set_comparison(Compare* new_compare);
    void set_selection(Select* new_select);
    void print_selection(std::ostream& out);
};

#endif //__SPREADSHEET_HPP__
