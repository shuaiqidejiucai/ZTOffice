#ifndef PST_NOTES_H
#define PST_NOTES_H

#include "pst_base.h"
#include "pst_notesatom.h"
#include "pst_ppdrawing.h"
#include "pst_colorschemeatom.h"
#include "pst_progtags.h"
#include "pst_roundtriptheme12atom.h"
#include "pst_roundtripcolormapping12atom.h"
#include "pst_roundtripnotesmastertextstyles12atom.h"
class PST_Notes : public PST_Base
{
public:
    PST_Notes(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_NotesAtom> notesAtomPtr;
    QSharedPointer<PST_PPDrawing> ppdrwingPtr;
    QSharedPointer<PST_ColorSchemeAtom> colorSchemeAtomPtr;
    QSharedPointer<PST_ProgTags> protagesPtr;
    QSharedPointer<PST_RoundTripTheme12Atom> roundTripTheme12AtomPtr;
    QSharedPointer<PST_RoundTripColorMapping12Atom> roundTripMapping12AtomPtr;
    QSharedPointer<PST_RoundTripNotesMasterTextStyles12Atom> roundTripNotesMasterTextStyles12Atom;
};

#endif // PST_NOTES_H
