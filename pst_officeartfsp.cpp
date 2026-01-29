#include "pst_officeartfsp.h"

PST_OfficeArtFSP::PST_OfficeArtFSP(const QByteArray& srcData, const ST_Variable& var)
	:PST_Base(srcData, var) {}

int PST_OfficeArtFSP::parser()
{
	m_isParser = true;
	ST_Variable stVar;
	quint32 pos = ST_SP(stVar);
	SPID = GetFlagData<quint32>(m_srcData, pos);
	quint32 artFSPFlag = GetFlagData<quint32>(m_srcData, pos);
	fGroup = artFSPFlag & 0x1;
	fChild = (artFSPFlag) >> 1 & 0x1;
	fPatriarch = (artFSPFlag) >> 2 & 0x1;
	fDeleted = (artFSPFlag) >> 3 & 0x1;
	fOleShape = (artFSPFlag) >> 4 & 0x1;
	fHaveMaster = (artFSPFlag) >> 5 & 0x1;
	fFlipH = (artFSPFlag) >> 6 & 0x1;
	fFlipV = (artFSPFlag) >> 7 & 0x1;
	fConnector = (artFSPFlag) >> 8 & 0x1;
	fHaveAnchor = (artFSPFlag) >> 9 & 0x1;
	fBackground = (artFSPFlag) >> 10 & 0x1;
	fHaveSpt = (artFSPFlag) >> 11 & 0x1;
	unused = (artFSPFlag) >> 12 & 0xFFFFF;
	return 0;
}
