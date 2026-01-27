#ifndef PST_EXTERNALOLEEMBEDATOM_H
#define PST_EXTERNALOLEEMBEDATOM_H

#include "pst_base.h"

class PST_ExternalOleEmbedAtom : public PST_Base
{
public:
    PST_ExternalOleEmbedAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser() override;
};

#endif // PST_EXTERNALOLEEMBEDATOM_H
