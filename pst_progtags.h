#ifndef PST_PROGTAGS_H
#define PST_PROGTAGS_H

#include "pst_base.h"

class PST_ProgBinaryTag;
class PST_ProgTags : public PST_Base
{
public:
    PST_ProgTags(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;

    virtual void clearParserData()override;

    virtual int priority()override;

    QList<QSharedPointer<PST_ProgBinaryTag> > progBinTagList;
};

#endif // PST_PROGTAGS_H
