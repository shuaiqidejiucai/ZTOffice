#ifndef PST_TEXTHEADERATOM_H
#define PST_TEXTHEADERATOM_H

#include "pst_base.h"

class PST_TextHeaderAtom : public PST_Base
{
public:
    PST_TextHeaderAtom(const QByteArray& srcData);

    quint32 textType;
};

#endif // PST_TEXTHEADERATOM_H
