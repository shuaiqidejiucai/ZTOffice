#ifndef PST_TEXTSPECIALINFODEFAULTATOM_H
#define PST_TEXTSPECIALINFODEFAULTATOM_H

#include "pst_base.h"

class PST_TextSpecialInfoDefaultAtom : public PST_Base
{
public:
    PST_TextSpecialInfoDefaultAtom(const QByteArray& srcData);

    virtual int parser()override;
};

#endif // PST_TEXTSPECIALINFODEFAULTATOM_H
