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

class Compare_Column
{
protected:
    int column;
public:
    Compare_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    // If row_1 should come before row_2, return -1;
    // If row_1 should come after row_2, return 1;
    // If the ordering between row_1 and row_2 is not specified, return 0;
    virtual int compare(const Spreadsheet* sheet, int row_1, int row_2) const
    {
        auto& s1 = sheet->cell_data(row_1, column);
        auto& s2 = sheet->cell_data(row_2, column);
        return compare(s1, s2);
    }

    // Derived classes can instead implement this simpler interface.
    virtual int compare(const std::string& s1, const std::string& s2) const = 0;
};

class Compare_String: public Compare_Column
{
public:
    Compare_String(const Spreadsheet* sheet, const std::string& name)
        :Compare_Column(sheet,name)
    {}

    virtual int compare(const std::string& s1, const std::string& s2) const
    {
        if(s1<s2) return -1;
        return s1>s2;
    }
};

class Compare_String: public Compare_Column
{
public:
    Compare_String(const Spreadsheet* sheet, const std::string& name)
        :Compare_Column(sheet,name)
    {}

    virtual int compare(const std::string& s1, const std::string& s2) const
    {
        if(s1<s2) return -1;
        return s1>s2;
    }
};

#endif //__COMPARE_HPP__
