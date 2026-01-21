#ifndef PST_SLIDE_H
#define PST_SLIDE_H

#include "pst_base.h"
#include "pst_slideatom.h"
#include "pst_ppdrawing.h"
#include "pst_colorschemeatom.h"
#include "pst_progtags.h"
#include "pst_roundtripcontentmasterid12atom.h"
class PST_Slide : public PST_Base
{
public:
    PST_Slide(const QByteArray& srcData);

    PST_SlideAtom slideAtom;
    PST_PPDrawing ppdwing;
    PST_ColorSchemeAtom colorSchemeAtom;
    PST_ProgTags proTags;
    PST_RoundTripContentMasterId12Atom roundTripContentMasterId12Atom;
};

#endif // PST_SLIDE_H
