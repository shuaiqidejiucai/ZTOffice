#ifndef PST_VIEWINFOATOM_H
#define PST_VIEWINFOATOM_H

#include "pst_base.h"

class PST_ViewInfoAtom : public PST_Base
{
public:
    PST_ViewInfoAtom(const QByteArray& srcData);

    virtual int parser()override;
};

#endif // PST_VIEWINFOATOM_H
