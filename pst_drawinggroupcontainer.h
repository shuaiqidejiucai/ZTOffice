#ifndef PST_DRAWINGGROUPCONTAINER_H
#define PST_DRAWINGGROUPCONTAINER_H

#include "pst_base.h"
#include "odraw_officeartbstorecontainer.h"
#include "pst_msofbtopt.h"
#include "odraw_officeartsplitmenucolorcontainer.h"
class PST_DrawingGroupAtom : public PST_Base
{
public:
    PST_DrawingGroupAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
};

class PST_DrawingGroupContainer : public PST_Base
{
public:
    PST_DrawingGroupContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser() override;

    QSharedPointer<PST_DrawingGroupAtom> dwGroupAtom;
    QSharedPointer<ODRAW_OfficeArtBStoreContainer> odrawOABSContainer;
    QSharedPointer<PST_MSOfbtOPT> msofbtOPT;
    QSharedPointer<ODRAW_OfficeArtSplitMenuColorContainer> oasColorContainter;
};

#endif // PST_DRAWINGGROUPCONTAINER_H
