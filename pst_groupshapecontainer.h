#ifndef PST_GROUPSHAPECONTAINER_H
#define PST_GROUPSHAPECONTAINER_H

#include "pst_base.h"

class PST_ShapeContainer;
class PST_GroupShapeContainer : public PST_Base
{
public:
    PST_GroupShapeContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QList<QSharedPointer<PST_ShapeContainer> > shapeContainerList;
};

#endif // PST_GROUPSHAPECONTAINER_H
