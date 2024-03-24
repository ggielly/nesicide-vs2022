/*
** FamiTracker - NES/Famicom sound tracker
** Copyright (C) 2005-2014  Jonathan Liss
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
** Library General Public License for more details.  To obtain a 
** copy of the GNU Library General Public License, write to the Free 
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/

#include "stdafx.h"
#include "DocumentWrapper.h"

// This will implement the CFamiTrackerDocInterface for export plugins

CFamiTrackerDocWrapper::CFamiTrackerDocWrapper(CFamiTrackerDoc* pDocument, const int iTrack) :
	m_pDocument(pDocument),
	m_iTrack(iTrack)
{
}

void CFamiTrackerDocWrapper::GetNoteData(const unsigned int Frame, const unsigned int Channel, const unsigned int Row,
                                         stChanNote* Data) const
{
	m_pDocument->GetNoteData(m_iTrack, Frame, Channel, Row, Data);
}

unsigned int CFamiTrackerDocWrapper::GetFrameCount() const
{
	return m_pDocument->GetFrameCount(m_iTrack);
}

unsigned int CFamiTrackerDocWrapper::GetPatternLength() const
{
	return m_pDocument->GetPatternLength(m_iTrack);
}

unsigned int CFamiTrackerDocWrapper::GetSongSpeed() const
{
	return m_pDocument->GetSongSpeed(m_iTrack);
}

CSequenceInterface const* CFamiTrackerDocWrapper::GetSequence(const unsigned int Index, const int Type) const
{
	return m_pDocument->GetSequence(Index, Type);
}

int CFamiTrackerDocWrapper::GetSequenceCount(const int Type) const
{
	return m_pDocument->GetSequenceCount(Type);
}

int CFamiTrackerDocWrapper::GetInstrumentCount() const
{
	return m_pDocument->GetInstrumentCount();
}

CInstrument2A03Interface const* CFamiTrackerDocWrapper::Get2A03Instrument(const int Instrument) const
{
	CInstrument* pInstrument = m_pDocument->GetInstrument(Instrument);
	pInstrument->Release(); // Prevent memory leak, no instrument will be removed during export
	return dynamic_cast<CInstrument2A03Interface const *>(pInstrument);
}

unsigned int CFamiTrackerDocWrapper::GetNoteEffectType(const unsigned int Frame, const unsigned int Channel, const unsigned int Row,
                                                       const int Index) const
{
	stChanNote Note;
	m_pDocument->GetNoteData(m_iTrack, Frame, Channel, Row, &Note);
	return Note.EffNumber[Index];
}

unsigned int CFamiTrackerDocWrapper::GetNoteEffectParam(const unsigned int Frame, const unsigned int Channel, const unsigned int Row,
                                                        const int Index) const
{
	stChanNote Note;
	m_pDocument->GetNoteData(m_iTrack, Frame, Channel, Row, &Note);
	return Note.EffParam[Index];
}

int CFamiTrackerDocWrapper::GetSampleCount() const
{
	return m_pDocument->GetSampleCount();
}

void CFamiTrackerDocWrapper::GetSampleName(const unsigned int Index, char* Name) const
{
	strncpy(Name, m_pDocument->GetSample(Index)->GetName(), CDSample::MAX_NAME_SIZE);
}

int CFamiTrackerDocWrapper::GetSampleSize(const unsigned int Sample) const
{
	return m_pDocument->GetSample(Sample)->GetSize();
}

char CFamiTrackerDocWrapper::GetSampleData(const unsigned int Sample, const unsigned int Offset) const
{
	return *(m_pDocument->GetSample(Sample)->GetData() + Offset);
}
