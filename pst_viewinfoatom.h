#ifndef PST_VIEWINFOATOM_H
#define PST_VIEWINFOATOM_H

#include "pst_base.h"

class PSTParser_EXPORT PST_ViewInfoAtom : public PST_Base
{
public:
    PST_ViewInfoAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_VIEWINFOATOM_H
