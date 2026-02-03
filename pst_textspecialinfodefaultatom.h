#ifndef PST_TEXTSPECIALINFODEFAULTATOM_H
#define PST_TEXTSPECIALINFODEFAULTATOM_H

#include "pst_base.h"

class PST_TextSpecialInfoDefaultAtom : public PST_Base
{
public:
    PST_TextSpecialInfoDefaultAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    virtual void clearParserData()override;

    virtual int priority()override;
};

#endif // PST_TEXTSPECIALINFODEFAULTATOM_H
