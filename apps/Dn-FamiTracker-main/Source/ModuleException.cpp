/*
** FamiTracker - NES/Famicom sound tracker
** Copyright (C) 2005-2020 Jonathan Liss
**
** 0CC-FamiTracker is (C) 2014-2018 HertzDevil
**
** Dn-FamiTracker is (C) 2020-2024 D.P.C.M.
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** Library General Public License for more details. To obtain a
** copy of the GNU Library General Public License, write to the Free
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/

#include <cstdarg>
#include "ModuleException.h"

CModuleException::CModuleException() :
	std::exception(),
	m_strError(),
	m_strFooter()
{
}

const std::string CModuleException::GetErrorString() const
{
	std::string out;
	const std::size_t COUNT = m_strError.size();
	for (std::size_t i = 0; i < COUNT; ) {
		out += *m_strError[i];
		if (++i == COUNT) break;
		out += '\n';
	}
	if (m_strFooter) {
		out += '\n';
		out += *m_strFooter;
	}
	return out;
}

void CModuleException::SetFooter(std::string footer)
{
	m_strFooter.reset(new std::string(footer));
}