#ifndef PST_EXTERNALOLEEMBEDATOM_H
#define PST_EXTERNALOLEEMBEDATOM_H

#include "pst_base.h"

class PST_ExternalOleEmbedAtom : public PST_Base
{
public:
    PST_ExternalOleEmbedAtom(const QByteArray& srcData);

    virtual int parser() override;
};

#endif // PST_EXTERNALOLEEMBEDATOM_H
