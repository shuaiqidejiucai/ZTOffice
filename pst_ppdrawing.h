#ifndef PST_PPDRAWING_H
#define PST_PPDRAWING_H

#include "pst_base.h"

class PST_DrawingContainer;
class PST_PPDrawing : public PST_Base
{
public:
    PST_PPDrawing(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_DrawingContainer> dwingContinerPtr;
};

#endif // PST_PPDRAWING_H
