#ifndef __COMPARE_HPP__
#define __COMPARE_HPP__

class Compare
{
public:
    virtual ~Compare() = default;

    // If row_1 should come before row_2, return -1;
    // If row_1 should come after row_2, return 1;
    // If the ordering between row_1 and row_2 is not specified, return 0;
    virtual int compare(int row_1, int row_2) const = 0;
};

#endif //__COMPARE_HPP__
