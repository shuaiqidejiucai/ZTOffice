#include "pst_environment.h"

PST_Environment::PST_Environment(const QByteArray &srcData, const ST_Variable& var)
	:PST_Base(srcData, var)
{

}

int PST_Environment::parser()
{
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
			QSharedPointer<PST_SrKinsoku> srKinsoKuPtr(new PST_SrKinsoku(m_srcData, stVar));
			srKinSoKuList.append(srKinsoKuPtr);
			addChildNodePtr(srKinsoKuPtr);
		}
			break;
		case RT_FontCollection:
		{
			QSharedPointer<PST_FontCollection> fontCollPtr(new PST_FontCollection(m_srcData, stVar));
			fontCollectionList.append(fontCollPtr);
			addChildNodePtr(fontCollPtr);
		}
			break;
		case RT_TextCharFormatExceptionAtom:
		{
			QSharedPointer<PST_TextCharFormatExceptionAtom> txtCharFormExAtomPtr(new PST_TextCharFormatExceptionAtom(m_srcData,stVar));
			textFormatExAtomList.append(txtCharFormExAtomPtr);
			addChildNodePtr(txtCharFormExAtomPtr);
		}
			break;
		case RT_TextParagraphFormatExceptionAtom:
		{
			QSharedPointer<PST_TextParagraphFormatExceptionAtom> txtParagraphExAtomPtr(new PST_TextParagraphFormatExceptionAtom(m_srcData, stVar));
			textParagraphFormatExAtomList.append(txtParagraphExAtomPtr);
			addChildNodePtr(txtParagraphExAtomPtr);
		}
			break;
		case RT_TextSpecialInfoDefaultAtom:
		{
			QSharedPointer<PST_TextSpecialInfoDefaultAtom> txtSpecialInfoDefAtomPtr(new PST_TextSpecialInfoDefaultAtom(m_srcData, stVar));
			textSpecialInfoDefaultAtomList.append(txtSpecialInfoDefAtomPtr);
			addChildNodePtr(txtSpecialInfoDefAtomPtr);
		}
			break;
		case RT_TextMasterStyleAtom:
		{
			QSharedPointer<PST_TxMasterStyleAtom> txtMasterStyAtomPtr(new PST_TxMasterStyleAtom(m_srcData, stVar));
			txMasterStyleAtomList.append(txtMasterStyAtomPtr);
			addChildNodePtr(txtMasterStyAtomPtr);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
    return Error_SuccessType;
}

void PST_Environment::clearParserData()
{
	srKinSoKuList.clear();
	fontCollectionList.clear();
	textFormatExAtomList.clear();
	textParagraphFormatExAtomList.clear();
	textSpecialInfoDefaultAtomList.clear();
	txMasterStyleAtomList.clear();
}

int PST_Environment::priority()
{
	return 0;
}
