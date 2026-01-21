#ifndef PST_DRAWINGGROUPCONTAINER_H
#define PST_DRAWINGGROUPCONTAINER_H

#include "pst_base.h"
#include "odraw_officeartbstorecontainer.h"
#include "pst_msofbtopt.h"
#include "odraw_officeartsplitmenucolorcontainer.h"
class PST_DrawingGroupAtom : public PST_Base
{
public:
    PST_DrawingGroupAtom(const QByteArray& srcData);
};

class PST_DrawingGroupContainer : public PST_Base
{
public:
    PST_DrawingGroupContainer(const QByteArray& srcData);

    PST_DrawingGroupAtom dwGroupAtom;
    ODRAW_OfficeArtBStoreContainer odrawOABSContainer;
    PST_MSOfbtOPT msofbtOPT;
    ODRAW_OfficeArtSplitMenuColorContainer oasColorContainter;
};

#endif // PST_DRAWINGGROUPCONTAINER_H
