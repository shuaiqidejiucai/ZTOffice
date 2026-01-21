#ifndef PST_GROUPSHAPECONTAINER_H
#define PST_GROUPSHAPECONTAINER_H

#include "pst_base.h"
#include "pst_shapecontainer.h"

class PST_GroupShapeContainer : public PST_Base
{
public:
    PST_GroupShapeContainer(const QByteArray& srcData);

    QList<PST_ShapeContainer> shapeContainerList;
};

#endif // PST_GROUPSHAPECONTAINER_H
