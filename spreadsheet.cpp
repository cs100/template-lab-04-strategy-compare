#include "spreadsheet.hpp"
#include "compare.hpp"
#include "select.hpp"

std::vector<std::vector<std::string> > data;
Compare* compare = 0;
Select* select = 0;

void Spreadsheet::set_comparison(Compare* new_compare)
{
    delete compare;
    compare = new_compare;
}

void Spreadsheet::set_selection(Select* new_select)
{
    delete select;
    select = new_select;
}

void Spreadsheet::print_selection(std::ostream& out)
{
    // Identify the rows that should be selected
    std::vector<int> selected_rows;
    for(int i=0; i<data.size(); i++)
        if(!select || select->select(i))
            selected_rows.push_back(i);

    // Sort the selected rows
    std::sort(selected_rows.begin(),selected_rows.end(),
        [](int a, int b)
        {
            return compare->compare(selected_rows[a],selected_rows[b]);
        });

    // Print out the selected rows
    for(auto row:selected_rows)
    {
        const auto& row_data = data[row];
        for(int c=0; c<row_data.size(); c++)
        {
            out<<row_data[c];
            if(c<=row_data.size()-1)
                out<<' ';
        }
        out<<'\n';
    }
}

#endif //__SPREADSHEET_HPP__
