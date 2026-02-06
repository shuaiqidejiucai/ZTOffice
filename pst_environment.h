#ifndef PST_ENVIRONMENT_H
#define PST_ENVIRONMENT_H

#include "pst_base.h"

class PST_SrKinsoku;
class PST_FontCollection;
class PST_TextCharFormatExceptionAtom;
class PST_TextParagraphFormatExceptionAtom;
class PST_TextSpecialInfoDefaultAtom;
class PST_TxMasterStyleAtom;
class PST_Environment : public PST_Base
{
public:
    PST_Environment(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QList<QSharedPointer<PST_SrKinsoku> > srKinSoKuList;
    QList<QSharedPointer<PST_FontCollection> > fontCollectionList;
    QList<QSharedPointer<PST_TextCharFormatExceptionAtom> > textFormatExAtomList;
    QList<QSharedPointer<PST_TextParagraphFormatExceptionAtom> > textParagraphFormatExAtomList;
    QList<QSharedPointer<PST_TextSpecialInfoDefaultAtom> > textSpecialInfoDefaultAtomList;
    QList<QSharedPointer<PST_TxMasterStyleAtom> > txMasterStyleAtomList;
};

#endif // PST_ENVIRONMENT_H
