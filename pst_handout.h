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

    PST_PPDrawing ppDwing;
    PST_ColorSchemeAtom colorSchemeAtom;
    PST_RoundTripTheme12Atom RTT12Atom;
    PST_RoundTripColorMapping12Atom RTCMappingAtom;
};

#endif // PST_HANDOUT_H
