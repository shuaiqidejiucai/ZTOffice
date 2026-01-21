#ifndef PST_PPDRAWINGGROUP_H
#define PST_PPDRAWINGGROUP_H

#include "pst_base.h"
#include "pst_drawinggroupcontainer.h"

class PST_PPDrawingGroup : public PST_Base
{
public:
    PST_PPDrawingGroup(const QByteArray& srcData);

    QList<PST_DrawingGroupContainer> dwGroupContainterList;
};

#endif // PST_PPDRAWINGGROUP_H
