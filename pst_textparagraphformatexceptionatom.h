#ifndef PST_TEXTPARAGRAPHFORMATEXCEPTIONATOM_H
#define PST_TEXTPARAGRAPHFORMATEXCEPTIONATOM_H

#include "pst_base.h"

class PSTParser_EXPORT PST_TextParagraphFormatExceptionAtom : public PST_Base
{
public:
    PST_TextParagraphFormatExceptionAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_TEXTPARAGRAPHFORMATEXCEPTIONATOM_H
