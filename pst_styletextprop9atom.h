#ifndef PST_STYLETEXTPROP9ATOM_H
#define PST_STYLETEXTPROP9ATOM_H

#include "pst_base.h"

class PSTParser_EXPORT PST_StyleTextProp9Atom : public PST_Base
{
public:
    PST_StyleTextProp9Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_STYLETEXTPROP9ATOM_H
