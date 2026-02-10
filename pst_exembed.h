#ifndef PST_EXEMBED_H
#define PST_EXEMBED_H

#include "pst_base.h"

class PST_ExternalOleObjectAtom;
class PST_ExternalOleEmbedAtom;
class PST_CString;
class PSTParser_EXPORT PST_ExEmbed : public PST_Base
{
public:
    PST_ExEmbed(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_ExternalOleEmbedAtom> exOleEmbedAtom;
    QSharedPointer<PST_ExternalOleObjectAtom> exOleObjAtom;
    QList<QSharedPointer<PST_CString> > cstringList;
};

#endif // PST_EXEMBED_H
