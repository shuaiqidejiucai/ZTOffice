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

    PST_NotesAtom notesAtom;
    PST_PPDrawing ppdrwing;
    PST_ColorSchemeAtom colorSchemeAtom;
    PST_ProgTags protages;
};

#endif // PST_NOTES_H
