#include "pst_shapecontainer.h"

PST_ShapeContainer::PST_ShapeContainer(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData,var) {}

int PST_ShapeContainer::parser()
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
		case COMMON_OfficeArtFSPGR:
		{
			officeArtFSPGRPtr = QSharedPointer<PST_OfficeArtFSPGR>::create(m_srcData, stVar);
		}
		break;
		case COMMON_OfficeArtFSP:
		{
			officeArtFSPPtr = QSharedPointer<PST_OfficeArtFSP>::create(m_srcData, stVar);
		}
			break;
		case COMMON_OfficeArtFOPT:
		{
			msoFbtOPTPtr = QSharedPointer<PST_MSOfbtOPT>::create(m_srcData, stVar);
		}
			break;
		case HeadRecord_OfficeArtClientAnchor:
		{
			officeArtClientAnchorPtr = QSharedPointer<OfficeArtClientAnchor>::create(m_srcData, stVar);
		}
			break;
		case HeadRecord_OfficeArtClientData:
		{
			shapeClientContainerPtr = QSharedPointer<PST_ShapeClientContainer>::create(m_srcData, stVar);
		}
			break;
		case HeadRecord_OfficeArtClientTextbox:
		{
			clientTxtBoxPtr = QSharedPointer<PST_ClientTextBox>::create(m_srcData, stVar);
		}
			break;
		case COMMON_OfficeArtTertiaryFOPT:
		{
			msoTertiaryOPTPtr = QSharedPointer<PST_MSOfbtTertiaryOPT>::create(m_srcData, stVar);
		}
			break;
		case COMMON_OfficeArtSpContainer:
		{
			officeArtSpConPtr = QSharedPointer<OfficeArtSpContainer>::create(m_srcData, stVar);
		}
			break;
		default:
			break;
		}
		pos = ST_EP(stVar);
	} while (pos < ST_EP(m_STVar));
	return 0;
}
