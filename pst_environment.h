#ifndef PST_ENVIRONMENT_H
#define PST_ENVIRONMENT_H

#include "pst_base.h"
#include "pst_srkinsoku.h"
#include "pst_fontcollection.h"
#include "pst_textcharformatexceptionatom.h"
#include "pst_textparagraphformatexceptionatom.h"
#include "pst_textspecialinfodefaultatom.h"
#include "pst_txmasterstyleatom.h"

class PST_Environment : public PST_Base
{
public:
    PST_Environment(const QByteArray& srcData);

    QList<QSharedPointer<PST_SrKinsoku> > srKinSoKuList;
    QList<QSharedPointer<PST_FontCollection> > fontCollectionList;
    QList<QSharedPointer<PST_TextCharFormatExceptionAtom> > textFormatExAtomList;
    QList<QSharedPointer<PST_TextParagraphFormatExceptionAtom> > textParagraphFormatExAtomList;
    QList<QSharedPointer<PST_TextSpecialInfoDefaultAtom> > textSpecialInfoDefaultAtomList;
    QList<QSharedPointer<PST_TxMasterStyleAtom> > txMasterStyleAtomList;
};

#endif // PST_ENVIRONMENT_H
