#ifndef PST_PPDRAWINGGROUP_H
#define PST_PPDRAWINGGROUP_H

#include "pst_base.h"

class PST_DrawingGroupContainer;
class PST_PPDrawingGroup : public PST_Base
{
public:
    PST_PPDrawingGroup(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr) override;

    virtual void clearParserData()override;

    virtual int priority()override;
    QList<QSharedPointer<PST_DrawingGroupContainer> > dwGroupContainterList;
};

#endif // PST_PPDRAWINGGROUP_H
