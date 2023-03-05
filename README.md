# Simple W2812 RMT driver for ESP-IDF
base on [Lang-ship](https://lang-ship.com/blog/)

``` cmake:CMakeLists.txt
idf_component_register(SRCS "main.cpp"
				simple_ws2812_rmt_esp-idf
                    INCLUDE_DIRS ".")

```

``` cpp:main.cpp
#include "RMT_WS2812.hpp"

#define CONFIG_MAX_BRIGHTNESS  20

void app_main(void) {
	ESP_LOGI(tag, "Blink LED");
	
	RMT_WS2812 *led = new RMT_WS2812(esp_board::ATOMS3_lite);
	ESP_LOGI(tag, "%p", led);
	led->clear();

	int color = 0;
	while (true) {
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		ESP_LOGD(tag, "Idleing");
		
		led->setPixel(0, 
			color & 0b001 ? 255 : 0,
			color & 0b010 ? 255 : 0,
			color & 0b100 ? 255 : 0);
		led->setBrightness(CONFIG_MAX_BRIGHTNESS);
		led->refresh();
		++color;
		ESP_LOGI(tag, "color: %d", color);
	}
}
```