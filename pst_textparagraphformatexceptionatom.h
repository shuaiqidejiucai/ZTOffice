#ifndef PST_TEXTPARAGRAPHFORMATEXCEPTIONATOM_H
#define PST_TEXTPARAGRAPHFORMATEXCEPTIONATOM_H

#include "pst_base.h"

class PST_TextParagraphFormatExceptionAtom : public PST_Base
{
public:
    PST_TextParagraphFormatExceptionAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
};

#endif // PST_TEXTPARAGRAPHFORMATEXCEPTIONATOM_H
