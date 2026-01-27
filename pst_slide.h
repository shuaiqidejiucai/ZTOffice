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
    PST_Slide(const QByteArray& srcData, const ST_Variable& var);

    QSharedPointer<PST_SlideAtom> slideAtomPtr;
    QSharedPointer<PST_PPDrawing> ppdwingPtr;
    QSharedPointer<PST_ColorSchemeAtom> colorSchemeAtomPtr;
    QSharedPointer<PST_ProgTags> proTagsPtr;
    QSharedPointer<PST_RoundTripContentMasterId12Atom> roundTripContentMasterId12AtomPtr;
};

#endif // PST_SLIDE_H
