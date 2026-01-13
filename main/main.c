#include "esp_lv_adapter.h"  // Includes display & input adapters


void app_main(void)
{
    // Step 0: Create your esp_lcd panel and (optionally) panel_io with esp_lcd APIs
    esp_lcd_panel_handle_t panel = /* ... */;
    esp_lcd_panel_io_handle_t panel_io = /* ... or NULL */;

    // Step 1: Initialize the adapter
    esp_lv_adapter_config_t cfg = ESP_LV_ADAPTER_DEFAULT_CONFIG();
    ESP_ERROR_CHECK(esp_lv_adapter_init(&cfg));

    // Step 2: Register a display (choose macro by interface)
    esp_lv_adapter_display_config_t disp_cfg = ESP_LV_ADAPTER_DISPLAY_SPI_WITH_PSRAM_DEFAULT_CONFIG(
        panel,           // LCD panel handle
        panel_io,        // LCD panel IO handle (can be NULL for some interfaces)
        480,             // Horizontal resolution
        320,             // Vertical resolution
        ESP_LV_ADAPTER_ROTATE_0 // Rotation
    );
    lv_display_t *disp = esp_lv_adapter_register_display(&disp_cfg);
    assert(disp != NULL);

    // Step 3: (Optional) Register input device(s)
    // Create touch handle using esp_lcd_touch API (implementation omitted here)
    // esp_lcd_touch_handle_t touch_handle = /* ... */;
    // esp_lv_adapter_touch_config_t touch_cfg = ESP_LV_ADAPTER_TOUCH_DEFAULT_CONFIG(disp, touch_handle);
    // lv_indev_t *touch = esp_lv_adapter_register_touch(&touch_cfg);
    // assert(touch != NULL);

    // Step 4: Start the adapter task
    ESP_ERROR_CHECK(esp_lv_adapter_start());

    // Step 5: Draw with LVGL (guarded by adapter lock for thread safety)
    if (esp_lv_adapter_lock(-1) == ESP_OK) {
        lv_obj_t *label = lv_label_create(lv_scr_act());
        lv_label_set_text(label, "Hello LVGL!");
        lv_obj_center(label);
        esp_lv_adapter_unlock();
    }
}