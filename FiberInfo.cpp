
#include "FiberInfo.h"
#include "FiberLinkDef.h"

FiberInfo::FiberInfo()
    : TObject(), x(0), y(0), num_pixel(0), avg_x(0.0f), avg_y(0.0f), avg_clr(0.0f)
    {}

FiberInfo::~FiberInfo()
{
}
