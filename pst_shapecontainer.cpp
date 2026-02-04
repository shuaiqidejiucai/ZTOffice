#include "pst_shapecontainer.h"
#include "pstsearch.h"
PST_ShapeContainer::PST_ShapeContainer(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_ShapeContainer::parser(PSTSearch* pSearchPtr)
{
	ST_Variable stVar;
	quint32 pos = ST_SP(m_STVar);

	do
	{
		if (!physicalStruct(pos, m_srcData, stVar))
		{
			return Error_FailedType;
		}
		switch (ST_TP(stVar))
		{
		case COMMON_OfficeArtFSPGR:
		{
			officeArtFSPGRPtr = QSharedPointer<PST_OfficeArtFSPGR>::create(m_srcData, stVar);
			addChildNodePtr(officeArtFSPGRPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, officeArtFSPGRPtr);
		}
		break;
		case COMMON_OfficeArtFSP:
		{
			officeArtFSPPtr = QSharedPointer<PST_OfficeArtFSP>::create(m_srcData, stVar);
			addChildNodePtr(officeArtFSPPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, officeArtFSPPtr);
		}
			break;
		case COMMON_OfficeArtFOPT:
		{
			msoFbtOPTPtr = QSharedPointer<PST_MSOfbtOPT>::create(m_srcData, stVar);
			addChildNodePtr(msoFbtOPTPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, msoFbtOPTPtr);
		}
			break;
		case HeadRecord_OfficeArtClientAnchor:
		{
			officeArtClientAnchorPtr = QSharedPointer<OfficeArtClientAnchor>::create(m_srcData, stVar);
			addChildNodePtr(officeArtClientAnchorPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, officeArtClientAnchorPtr);
		}
			break;
		case HeadRecord_OfficeArtClientData:
		{
			shapeClientContainerPtr = QSharedPointer<PST_ShapeClientContainer>::create(m_srcData, stVar);
			addChildNodePtr(shapeClientContainerPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, shapeClientContainerPtr);
		}
			break;
		case HeadRecord_OfficeArtClientTextbox:
		{
			clientTxtBoxPtr = QSharedPointer<PST_ClientTextBox>::create(m_srcData, stVar);
			addChildNodePtr(clientTxtBoxPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, clientTxtBoxPtr);
		}
			break;
		case COMMON_OfficeArtTertiaryFOPT:
		{
			msoTertiaryOPTPtr = QSharedPointer<PST_MSOfbtTertiaryOPT>::create(m_srcData, stVar);
			addChildNodePtr(msoTertiaryOPTPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, msoTertiaryOPTPtr);
		}
			break;
		case COMMON_OfficeArtSpContainer:
		{
			officeArtSpConPtr = QSharedPointer<OfficeArtSpContainer>::create(m_srcData, stVar);
			addChildNodePtr(officeArtSpConPtr);
			if (pSearchPtr) pSearchPtr->insertRecordMap(stVar.originPos, officeArtSpConPtr);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return Error_SuccessType;
}

void PST_ShapeContainer::clearParserData()
{
	officeArtFSPGRPtr.clear();
	officeArtFSPPtr.clear();
	msoFbtOPTPtr.clear();
	officeArtClientAnchorPtr.clear();
	shapeClientContainerPtr.clear();

	msoTertiaryOPTPtr.clear();
	officeArtSpConPtr.clear();

	clientTxtBoxPtr.clear();
}

int PST_ShapeContainer::priority()
{
	return 0;
}
