#ifndef PST_HANDOUT_H
#define PST_HANDOUT_H
#include "pst_base.h"

class PST_PPDrawing;
class PST_ColorSchemeAtom;
class PST_ProgTags;
class PST_RoundTripTheme12Atom;
class PST_RoundTripColorMapping12Atom;
class PST_Handout : public PST_Base
{
public:
    PST_Handout(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_PPDrawing> ppDwingPtr;
    QSharedPointer<PST_ColorSchemeAtom> colorSchemeAtomPtr;
    QSharedPointer<PST_ProgTags> proTagesPtr;
    QSharedPointer<PST_RoundTripTheme12Atom> RTT12AtomPtr;
    QSharedPointer<PST_RoundTripColorMapping12Atom> RTCMappingAtomPtr;
};

#endif // PST_HANDOUT_H
