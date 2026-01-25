#ifndef PST_TEXTCHARFORMATEXCEPTIONATOM_H
#define PST_TEXTCHARFORMATEXCEPTIONATOM_H

#include "pst_base.h"

class PST_TextCharFormatExceptionAtom : public PST_Base
{
public:
    PST_TextCharFormatExceptionAtom(const QByteArray& srcData);

    virtual int parser() override;
};

#endif // PST_TEXTCHARFORMATEXCEPTIONATOM_H
