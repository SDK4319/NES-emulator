#pragma once
#include<functional>
#include<array>
#include"PictureBus.h"
#include"MainBus.h"
#include"VScreen.h"
#include"ColorTable.h"



const int ScanlineCycleLength = 341;
const int ScanlineEndCycle = 340;
const int VisibleScanlines = 240;
const int ScanlineVisibleDots = 256;
const int FrameEndScanline = 261;

const int AttributeOffset = 0x3C0;

//Picture Process Unit
class PPU
{

public:
	PPU(PictureBus& bus, VScreen& screen);
	void step();
	void reset();

	void setInterruptCallback(std::function<void(void)> cb);
	void doDMA(const byte* page_ptr);

	//Callbacks mapped to CPU address space
	//Addresses written to by the program
	void control(byte ctrl);
	void setMask(byte mask);
	void setOAMAddress(byte addr);
	void setDataAddress(byte addr);
	void setScroll(byte scroll);
	void setData(byte data);

	//Read by the program
	byte getStatus();
	byte getData();
	byte getOAMData();
	void setOAMData(byte value);

private:
	byte readOAM(byte addr);
	void writeOAM(byte addr, byte value);
	byte read(Addr addr);
	PictureBus& m_bus;
	VScreen& m_screen;
	std::function<void(void)> m_vblankCallback;
	std::vector<byte> m_spriteMemory;
	std::vector<byte> m_scanlineSprites;

	enum State {
		PreRender,
		Render,
		PostRender,
		VerticalBlank
	} m_pipelineState;
	int m_cycle;
	int m_scanline;
	bool m_evenFrame;

	bool m_vblank;
	bool m_sprZeroHit;

	//Register
	Addr m_dataAddress;
	Addr m_tempAddress;
	byte m_fineXScroll;
	bool m_firstWrite;
	byte m_dataBuffer;

	byte m_spriteDataAddress;

	//Setup flags and variables
	bool m_longSprites;
	bool m_generateInterrupt;

	bool m_greyscaleMode;
	bool m_showSprites;
	bool m_showBackground;
	bool m_hideEdgeSprites;
	bool m_hideEdgeBackground;


	enum CharacterPage {
		Low,
		High,
	}	m_bgPage,
		m_sprPage;
	Addr m_dataAddrIncrement;
	std::vector<std::vector<cv::Scalar>> m_pictureBuffer;
};

