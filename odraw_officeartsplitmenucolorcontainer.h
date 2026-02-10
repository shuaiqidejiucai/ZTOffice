#ifndef ODRAW_OFFICEARTSPLITMENUCOLORCONTAINER_H
#define ODRAW_OFFICEARTSPLITMENUCOLORCONTAINER_H

#include "pst_base.h"

class PSTParser_EXPORT ODRAW_OfficeArtSplitMenuColorContainer : public PST_Base
{
public:
    ODRAW_OfficeArtSplitMenuColorContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch * pSearchPtr = nullptr) override;

    virtual void clearParserData() override;

    virtual int priority()override;
};

#endif // ODRAW_OFFICEARTSPLITMENUCOLORCONTAINER_H
