#pragma once

#include "esp_log.h"
#include "driver/rmt.h"

class RMT_WS2812 {
	enum class esp_board {
		ATOMS3_lite,
		ATOM_Matrix,
		STAMP_C3,
	};

    private:
	static void IRAM_ATTR ws2812_rmt_adapter(const void *src, rmt_item32_t *dest, size_t src_size, size_t wanted_num, size_t *translated_size, size_t *item_num);
	void initialize();

	static uint32_t ws2812_t0h_ticks;
	static uint32_t ws2812_t1h_ticks;
	static uint32_t ws2812_t0l_ticks;
	static uint32_t ws2812_t1l_ticks;
	static uint8_t ws2812_brightness;	// 0-100

    public:
	RMT_WS2812(rmt_channel_t channel, gpio_num_t gpio, uint16_t ledNum);
	RMT_WS2812(esp_board esp);

	esp_err_t clear(uint32_t timeout_ms = 200);
	esp_err_t refresh(uint32_t timeout_ms = 200);
	esp_err_t setPixel(uint32_t index, uint8_t red, uint8_t green, uint8_t blue);
	void setBrightness(uint8_t brightness);

	const uint16_t WS2812_T0H_NS	 = 350;
	const uint16_t WS2812_T0L_NS	 = 1000;
	const uint16_t WS2812_T1H_NS	 = 1000;
	const uint16_t WS2812_T1L_NS	 = 350;
	const uint16_t WS2812_RESET_US = 280;

    private:
	rmt_channel_t _rmtChannel;
	gpio_num_t _rmtGpio;
	uint32_t _ledNum;
	uint8_t *_buffer;
	const char *TAG = "RMT_WS2812";
};
