#ifndef PST_HANDOUT_H
#define PST_HANDOUT_H
#include "pst_base.h"
#include "pst_ppdrawing.h"
#include "pst_colorschemeatom.h"
#include "pst_progtags.h"
#include "pst_roundtripcolormapping12atom.h"
#include "pst_roundtriptheme12atom.h"
class PST_Handout : public PST_Base
{
public:
    PST_Handout(const QByteArray& srcData);

    QSharedPointer<PST_PPDrawing> ppDwingPtr;
    QSharedPointer<PST_ColorSchemeAtom> colorSchemeAtomPtr;
    QSharedPointer<PST_ProgTags> proTagesPtr;
    QSharedPointer<PST_RoundTripTheme12Atom> RTT12AtomPtr;
    QSharedPointer<PST_RoundTripColorMapping12Atom> RTCMappingAtomPtr;
};

#endif // PST_HANDOUT_H
