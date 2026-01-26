#ifndef PST_PROGBINARYTAG_H
#define PST_PROGBINARYTAG_H

#include "pst_base.h"
#include "pst_cstring.h"
#include "pst_binarytagdata.h"
class PST_ProgBinaryTag : public PST_Base
{
public:
    PST_ProgBinaryTag(const QByteArray& srcData);

    virtual int parser()override;

    QSharedPointer<PST_CString> ctring;
    QSharedPointer<PST_BinaryTagData> binTagData;
};

#endif // PST_PROGBINARYTAG_H
