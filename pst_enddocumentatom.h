#ifndef PST_ENDDOCUMENTATOM_H
#define PST_ENDDOCUMENTATOM_H

#include "pst_base.h"

class PST_EndDocumentAtom : public PST_Base
{
public:
    PST_EndDocumentAtom(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser(PSTSearch* pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_ENDDOCUMENTATOM_H
