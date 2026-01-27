#ifndef PST_EXEMBED_H
#define PST_EXEMBED_H

#include "pst_base.h"
#include "pst_externaloleembedatom.h"
#include "pst_externaloleobjectatom.h"
#include "pst_cstring.h"
class PST_ExEmbed : public PST_Base
{
public:
    PST_ExEmbed(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser() override;


    QSharedPointer<PST_ExternalOleEmbedAtom> exOleEmbedAtom;
    QSharedPointer<PST_ExternalOleObjectAtom> exOleObjAtom;
    QList<QSharedPointer<PST_CString> > cstringList;
};

#endif // PST_EXEMBED_H
