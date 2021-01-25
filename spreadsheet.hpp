#ifndef __SPREADSHEET_HPP__
#define __SPREADSHEET_HPP__

#include <string>
#include <initializer_list>
#include <vector>
#include <iosfwd>

class Compare;
class Select;

class Spreadsheet
{
    std::vector<std::string> column_names;
    std::vector<std::vector<std::string> > data;
    Compare* compare = 0;
    Select* select = 0;

public:
    ~Spreadsheet();

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

    void clear();
    void set_column_names(std::initializer_list<std::string> names);
    void add_row(std::initializer_list<std::string> row_data);
    int get_column_by_name(const std::string& name);
};

#endif //__SPREADSHEET_HPP__
