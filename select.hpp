#ifndef __SELECT_HPP__
#define __SELECT_HPP__

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(int row) const = 0;
};

#endif //__SELECT_HPP__
