#ifndef PST_SHAPECLIENTCONTAINER_H
#define PST_SHAPECLIENTCONTAINER_H

#include "pst_base.h"

class PST_OEPlaceHolderAtom;
class PST_ProgTags;
class PST_ShapeClientContainer : public PST_Base
{
public:
    PST_ShapeClientContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;

    virtual void clearParserData()override;

    virtual int priority()override;

    QSharedPointer<PST_OEPlaceHolderAtom> oePlaceHolderAtom;
    //QSharedPointer<PST_RoundTripHFPlaceholder12Atom> roundTripHF12Atom;
    //QSharedPointer<PST_ExternalObjectRefAtom> exObjRefAtom;
    QSharedPointer<PST_ProgTags> progTagsPtr;
};

#endif // PST_SHAPECLIENTCONTAINER_H
