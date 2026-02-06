#ifndef PST_SLIDE_H
#define PST_SLIDE_H

#include "pst_base.h"

class PST_SlideAtom;
class PST_PPDrawing;
class PST_ColorSchemeAtom;
class PST_ProgTags;
class PST_RoundTripContentMasterId12Atom;
class PST_Slide : public PST_Base
{
public:
    PST_Slide(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_SlideAtom> slideAtomPtr;
    QSharedPointer<PST_PPDrawing> ppdwingPtr;
    QSharedPointer<PST_ColorSchemeAtom> colorSchemeAtomPtr;
    QSharedPointer<PST_ProgTags> proTagsPtr;
    QSharedPointer<PST_RoundTripContentMasterId12Atom> roundTripContentMasterId12AtomPtr;
};

#endif // PST_SLIDE_H
