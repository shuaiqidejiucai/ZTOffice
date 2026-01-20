#ifndef PST_EXEMBED_H
#define PST_EXEMBED_H

#include "pst_base.h"
#include "pst_externaloleembedatom.h"
#include "pst_externaloleobjectatom.h"
#include "pst_cstring.h"
class PST_ExEmbed : public PST_Base
{
public:
    PST_ExEmbed(const QByteArray& srcData);
    QList<PST_ExternalOleEmbedAtom> exOleEmbedAtomList;
    Qlist<PST_ExternalOleObjectAtom> exOleObjAtomList;
    QList<PST_CString> cstringList;
};

#endif // PST_EXEMBED_H
