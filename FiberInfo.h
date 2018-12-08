
#ifndef FIBERINFO_HEADER
#define FIBERINFO_HEADER

#include <TObject.h>


class FiberInfo: public TObject
{
public:
    int x, y;
    int num_pixel;
    float avg_x, avg_y;
    float avg_clr;

    FiberInfo();
    virtual ~FiberInfo();

    ClassDef(FiberInfo, 1);
};

#endif
