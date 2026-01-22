#ifndef PST_NOTES_H
#define PST_NOTES_H

#include "pst_base.h"
#include "pst_notesatom.h"
#include "pst_ppdrawing.h"
#include "pst_colorschemeatom.h"
#include "pst_progtags.h"
class PST_Notes : public PST_Base
{
public:
    PST_Notes(const QByteArray& srcData);

    QSharedPointer<PST_NotesAtom> notesAtomPtr;
    QSharedPointer<PST_PPDrawing> ppdrwingPtr;
    QSharedPointer<PST_ColorSchemeAtom> colorSchemeAtomPtr;
    QSharedPointer<PST_ProgTags> protagesPtr;
};

#endif // PST_NOTES_H
