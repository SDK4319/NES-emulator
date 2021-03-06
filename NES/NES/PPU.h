#pragma once
#include<cstdint>
#include<memory>
#include"Cartridge.h"
#include<opencv2/opencv.hpp>

class PPU
{
public:
	PPU();
	~PPU();

private:
	uint8_t tblName[2][1024];
	uint8_t tblPattern[2][4096];
	uint8_t tblPalette[32];

private:
	cv::Scalar palScreen[0x40];
	cv::Mat sprScreen = cv::Mat(cv::Size(256, 240),CV_8UC3);
	cv::Mat sprNameTable[2] = { cv::Mat(cv::Size(256, 240),CV_8UC3) ,cv::Mat(cv::Size(256, 240),CV_8UC3) };
	cv::Mat sprPatternTable[2] = { cv::Mat(cv::Size(128,128), CV_8UC3), cv::Mat(cv::Size(128,128),CV_8UC3) };

public:
	cv::Mat& getScreen();
	cv::Mat& getNameTable(uint8_t i);
	cv::Mat& getPatternTable(uint8_t i, uint8_t palette);

	cv::Scalar& getColorFromPaletteRam(uint8_t i, uint8_t palette);

	bool frame_complete = false;


private:

	union {
		struct {
			uint8_t unused : 5;
			uint8_t sprite_overflow : 1;
			uint8_t sprite_zero_hit : 1;
			uint8_t vertical_blank : 1;
		};

		uint8_t reg;
	} status;

	union {
		struct {
			uint8_t grayscale : 1;
			uint8_t render_background_left : 1;
			uint8_t render_sprites_left : 1;
			uint8_t render_background : 1;
			uint8_t render_sprites : 1;
			uint8_t enhance_red : 1;
			uint8_t enhance_green : 1;
			uint8_t enhance_blud : 1;
		};

		uint8_t reg;
	} mask;

	union PPUCTRL {
		struct {
			uint8_t nametable_x : 1;
			uint8_t nametable_y : 1;
			uint8_t increment_mode : 1;
			uint8_t pattern_sprite : 1;
			uint8_t pattern_background : 1;
			uint8_t sprite_size : 1;
			uint8_t slave_mode : 1;	// unused
			uint8_t enable_nmi : 1;
		};

		uint8_t reg;
	} control;


	union loopy_register {
		struct {
			uint16_t coarse_x : 5;
			uint16_t coarse_y : 5;
			uint16_t nametable_x : 1;
			uint16_t nametable_y : 1;
			uint16_t fine_y : 3;
			uint16_t unused : 1;
		};

		uint16_t reg = 0x0000;
	};

	loopy_register vram_addr;
	loopy_register tram_addr;

	uint8_t fine_x = 0x00; // pixel offset horizontal

	uint8_t address_latch = 0x00;
	uint8_t ppu_data_buffer = 0x00;

	int16_t scanline = 0;
	int16_t cycle = 0;

	// BG Render
	uint8_t bg_next_tile_id = 0x00;
	uint8_t bg_next_tile_attrib = 0x00;
	uint8_t bg_next_tile_lsb = 0x00;
	uint8_t bg_next_tile_msb = 0x00;
	uint16_t bg_shifter_pattern_lo = 0x0000;
	uint16_t bg_shifter_pattern_hi = 0x0000;
	uint16_t bg_shifter_attrib_lo = 0x0000;
	uint16_t bg_shifter_attrib_hi = 0x0000;

	// FG Sprite Render
	struct ObjectAttributeEntry {
		uint8_t y;
		uint8_t id;
		uint8_t attribute;
		uint8_t x;
	} OAM[64];


	uint8_t oam_addr = 0x00;

	ObjectAttributeEntry spriteScanline[8];
	uint8_t sprite_count;
	uint8_t sprite_shifter_pattern_lo[8];
	uint8_t sprite_shifter_pattern_hi[8];

	bool bSpriteZeroHitPossible = false;
	bool bSpriteZeroBeingRendered = false;

public:
	uint8_t* p_OAM = (uint8_t*)OAM;

	uint8_t cpuRead(uint16_t addr, bool readOnly = false);
	void cpuWrite(uint16_t addr, uint8_t data);

	uint8_t ppuRead(uint16_t addr, bool readOnly = false);
	void ppuWrite(uint16_t addr, uint8_t data);

private:
	std::shared_ptr<Cartridge> cart;

public:
	void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
	void clock();
	void reset();
	bool nmi = false;

};

