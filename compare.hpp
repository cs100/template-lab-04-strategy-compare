#ifndef __COMPARE_HPP__
#define __COMPARE_HPP__

class Compare
{
public:
    virtual ~Compare() = default;

    // If row_1 should come before row_2, return -1;
    // If row_1 should come after row_2, return 1;
    // If the ordering between row_1 and row_2 is not specified, return 0;
    virtual int compare(const Spreadsheet* sheet, int row_1, int row_2) const = 0;
};

class Compare_String: public Compare
{
    int column;
public:
    Compare_String(int column): column(column) {}

    virtual int compare(const Spreadsheet* sheet, int row_1, int row_2) const
    {
        auto& s1 = sheet->cell_data(row_1, column);
        auto& s2 = sheet->cell_data(row_2, column);
        if(s1 < s2) return -1;
        if(s2 < s1) return 1;
        return 0;
    }
};

#endif //__COMPARE_HPP__
