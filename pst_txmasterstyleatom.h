#ifndef PST_TXMASTERSTYLEATOM_H
#define PST_TXMASTERSTYLEATOM_H

#include "pst_base.h"

class PST_TxMasterStyleAtom : public PST_Base
{
public:
    PST_TxMasterStyleAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSeaechPtr)override;

    virtual void clearParserData()override;

    virtual int priority()override;
};

#endif // PST_TXMASTERSTYLEATOM_H
