#ifndef PST_MAINMASTER_H
#define PST_MAINMASTER_H
#include "pst_base.h"
#include "pst_slideatom.h"
#include "pst_colorschemeatom.h"
#include "pst_txmasterstyleatom.h"
#include "pst_roundtripoarttextstyles12atom.h"
#include "pst_progtags.h"
#include "pst_roundtripcolormapping12atom.h"
#include "pst_roundtriptheme12atom.h"
#include "pst_roundtripcontentmasterinfo12atom.h"
#include "pst_roundtriporiginalmainmasterid12atom.h"
#include "pst_cstring.h"
#include "pst_ppdrawing.h"
class PST_MainMaster : public PST_Base
{
public:
    PST_MainMaster(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    QSharedPointer<PST_SlideAtom> slideAtomPtr;
    QList<QSharedPointer<PST_ColorSchemeAtom> > colorSchemeAtomPtrList;
    QList<QSharedPointer<PST_TxMasterStyleAtom> > txMasterStyleAtomPtrList;
    QSharedPointer<PST_RoundTripOArtTextStyles12Atom> roundTripOArtTxtStyles12Atom;
    QSharedPointer<PST_PPDrawing> ppdDwingPtr;
    QSharedPointer<PST_ProgTags> progTagsPtr;
    QList<QSharedPointer<PST_RoundTripTheme12Atom> > roundTripTheme12AtomPtrList;
    QList<QSharedPointer<PST_RoundTripColorMapping12Atom> > roundTripColorMapping12AtomPtrList;
    QList<QSharedPointer<PST_RoundTripContentMasterInfo12Atom> > roundTripContentMasterInfo12AtomPtrList;
    QList<QSharedPointer<PST_RoundTripOriginalMainMasterId12Atom> > roundTripContentMasterId12AtomPtrList;
    QList<QSharedPointer<PST_CString> > cstringPtrList;

};

#endif // PST_MAINMASTER_H
