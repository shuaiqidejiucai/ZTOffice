#include "pst_environment.h"

PST_Environment::PST_Environment(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_Environment::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);
	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return -1;
		}
		switch (ST_TP(stVar))
		{
		case RT_Kinsoku:
		{
			QSharedPointer<PST_SrKinsoku> srKinsoKuPtr(new PST_SrKinsoku(m_srcData));
			srKinsoKuPtr->setSTVar(stVar);
			srKinSoKuList.append(srKinsoKuPtr);
		}
			break;
		case RT_FontCollection:
		{
			QSharedPointer<PST_FontCollection> fontCollPtr(new PST_FontCollection(m_srcData));
			fontCollPtr->setSTVar(stVar);
			fontCollectionList.append(fontCollPtr);
		}
			break;
		case RT_TextCharFormatExceptionAtom:
		{
			QSharedPointer<PST_TextCharFormatExceptionAtom> txtCharFormExAtomPtr(new PST_TextCharFormatExceptionAtom(m_srcData));
			txtCharFormExAtomPtr->setSTVar(stVar);
			textFormatExAtomList.append(txtCharFormExAtomPtr);
		}
			break;
		case RT_TextParagraphFormatExceptionAtom:
		{
			QSharedPointer<PST_TextParagraphFormatExceptionAtom> txtParagraphExAtomPtr(new PST_TextParagraphFormatExceptionAtom(m_srcData));
			txtParagraphExAtomPtr->setSTVar(stVar);
			textParagraphFormatExAtomList.append(txtParagraphExAtomPtr);
		}
			break;
		case RT_TextSpecialInfoDefaultAtom:
		{
			QSharedPointer<PST_TextSpecialInfoDefaultAtom> txtSpecialInfoDefAtomPtr(new PST_TextSpecialInfoDefaultAtom(m_srcData));
			txtSpecialInfoDefAtomPtr->setSTVar(stVar);
			textSpecialInfoDefaultAtomList.append(txtSpecialInfoDefAtomPtr);
		}
			break;
		case RT_TextMasterStyleAtom:
		{
			QSharedPointer<PST_TxMasterStyleAtom> txtMasterStyAtomPtr(new PST_TxMasterStyleAtom(m_srcData));
			txtMasterStyAtomPtr->setSTVar(stVar);
			txMasterStyleAtomList.append(txtMasterStyAtomPtr);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    return 0;
}
