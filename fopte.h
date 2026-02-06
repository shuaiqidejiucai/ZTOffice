#ifndef FOPTE_H
#define FOPTE_H

#include "pst_base.h"

//TODO:获取不用PST_Base
class Fopte : public PST_Base
{
public:
    Fopte(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSeaechPtr = nullptr) override;
    virtual void clearParserData() override;
    virtual int priority()override;
    quint16 pid;
    quint8 fBid;
    quint8 fComplex;
    quint32 op;
};

class FOPTEComplex : public PST_Base
{
public:
    FOPTEComplex(const QByteArray& srcData, const ST_Variable& var);
    virtual int parser(PSTSearch* pSearchPtr) override;
    virtual void clearParserData() override;
    virtual int priority()override;
};

#endif // FOPTE_H
