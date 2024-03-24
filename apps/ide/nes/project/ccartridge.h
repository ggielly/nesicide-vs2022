#ifndef CCARTRIDGE_H
#define CCARTRIDGE_H

#include "nes_emulator_core.h"
#include "cprojectbase.h"
#include "cprgrombanks.h"
#include "cchrrombanks.h"

using eMirrorMode = enum
{
	HorizontalMirroring = 0,
	VerticalMirroring = 1
};

class CCartridge : public CProjectBase
{
	Q_OBJECT

public:
	CCartridge(IProjectTreeViewItem* parent);
	~CCartridge() override;

	// Helper functions
	void initializeProject();
	void terminateProject();

	// Member Getters
	eMirrorMode getMirrorMode()
	{
		return m_mirrorMode;
	}

	int getMapperNumber()
	{
		return m_mapperNumber;
	}

	bool isBatteryBackedRam()
	{
		return m_hasBatteryBackedRam;
	}

	CPRGROMBanks* getPrgRomBanks()
	{
		return m_pPrgRomBanks;
	}

	CCHRROMBanks* getChrRomBanks()
	{
		return m_pChrRomBanks;
	}

	bool getFourScreen()
	{
		return m_fourScreen;
	}

	// Member Setters
	void setMirrorMode(eMirrorMode mirrorMode)
	{
		m_mirrorMode = mirrorMode;
	}

	void setMapperNumber(int mapperNumber)
	{
		m_mapperNumber = mapperNumber;
	}

	void setBatteryBackedRam(bool batteryBackedRam)
	{
		m_hasBatteryBackedRam = batteryBackedRam;
	}

	void setFourScreen(bool fourScreen)
	{
		m_fourScreen = fourScreen;
	}

	void exportROM();

	// IXMLSerializable Interface Implementation
	bool serialize(QDomDocument& doc, QDomNode& node) override;
	bool deserialize(QDomDocument& doc, QDomNode& node, QString& errors) override;

	// IProjectTreeViewItem Interface Implmentation
	QString caption() const override;

	void openItemEvent(CProjectTabWidget*) override
	{
	}

	// ICenterWidgetItem Interface Implementation

private:
	// Contained children
	CPRGROMBanks* m_pPrgRomBanks;
	CCHRROMBanks* m_pChrRomBanks;

	// Attributes
	eMirrorMode m_mirrorMode; // Mirror mode used in the emulator
	bool m_hasBatteryBackedRam; // Memory can be saved via RAM kept valid with a battery
	int m_mapperNumber; // Numeric ID of the cartridge mapper
	bool m_fourScreen;
};

#endif // CCARTRIDGE_H
