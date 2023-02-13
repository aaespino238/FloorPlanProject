#ifndef CLASSROOM_INC
#define CLASSROOM_INC

class Room
{
    size_t width, height, cut;
    //cut key
    //0 -> no cut
    //1 -> horizontal cut
    //2 -> vertical cut
    char name;
    bool internal;
    size_t xcoord;
    friend class FloorPlan;
    friend class LinkedBinaryTree;
public:
    Room(void)
        : width(0), height(0), cut(0), name('0'), internal(false), xcoord(0)
    {
    }

    Room(size_t w, size_t h, char n, bool i = false, size_t x = 0, size_t c = 0)
        : width(w), height(h), cut(c), name(n), internal(i), xcoord(x)
    {
    }

    bool isInternal(void)
    {
        return internal;
    }

    void setX(size_t x)
    {
        xcoord = x;
        return;
    }

    void makeCut(size_t c)
    {
        width = 0;
        height = 0;
        cut = c;
        return;
    }

    void setWidth(size_t w)
    {
        width = w;
        return;
    }

    void setHeight(size_t h)
    {
        height = h;
        return;
    }

    size_t getWidth(void)
    {
        return width;
    }

    size_t getHeight(void)
    {
        return height;
    }

    char getName(void)
    {
        return name;
    }

    Room& operator=(Room r)
    {
        width = r.width;
        height = r.height;
        name = r.name;
        internal = r.internal;
        xcoord = r.xcoord;
        cut = r.cut;
        return *this;
    }

    bool operator==(Room r)
    {
        return r.width == width ? (r.height == height ? true : false) : false;
    }

    bool operator!=(Room r)
    {
        return !(r == *this);
    }
};

#endif