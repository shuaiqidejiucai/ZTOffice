#ifndef PST_DRAWINGCONTAINER_H
#define PST_DRAWINGCONTAINER_H

#include "pst_base.h"
#include "pst_officeartfdg.h"
#include "pst_groupshapecontainer.h"
class PST_DrawingContainer : public PST_Base
{
public:
    PST_DrawingContainer(const QByteArray& srcData);

    PST_OfficeArtFDG officeArtFDG;
    PST_GroupShapeContainer groupShapeContainer;
};

#endif // PST_DRAWINGCONTAINER_H
