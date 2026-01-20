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

    QList<PST_SrKinsoku> srKinSoKuList;
    QList<PST_FontCollection> fontCollectionList;
    QList<PST_TextCharFormatExceptionAtom> textFormatExAtomList;
    QList<PST_TextParagraphFormatExceptionAtom> textParagraphFormatExAtomList;
    QList<PST_TextSpecialInfoDefaultAtom> textSpecialInfoDefaultAtomList;
    QList<PST_TxMasterStyleAtom> txMasterStyleAtomList;
};

#endif // PST_ENVIRONMENT_H
