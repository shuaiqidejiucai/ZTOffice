#ifndef PST_DRAWINGGROUPCONTAINER_H
#define PST_DRAWINGGROUPCONTAINER_H

#include "pst_base.h"

class PST_DrawingGroupAtom;
class ODRAW_OfficeArtBStoreContainer;
class PST_MSOfbtOPT;
class ODRAW_OfficeArtSplitMenuColorContainer;
class PSTParser_EXPORT PST_DrawingGroupAtom : public PST_Base
{
public:
    PST_DrawingGroupAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

class PSTParser_EXPORT PST_DrawingGroupContainer : public PST_Base
{
public:
    PST_DrawingGroupContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_DrawingGroupAtom> dwGroupAtom;
    QSharedPointer<ODRAW_OfficeArtBStoreContainer> odrawOABSContainer;
    QSharedPointer<PST_MSOfbtOPT> msofbtOPT;
    QSharedPointer<ODRAW_OfficeArtSplitMenuColorContainer> oasColorContainter;
};

#endif // PST_DRAWINGGROUPCONTAINER_H
