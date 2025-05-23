/*
oled display configuration
*/

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// render blank line
void oled_render_space(void) {
    oled_write_ln(" ", false);
}

// Render active layer state
static void oled_render_layer_state(void) {
    // 'layer_adjust', 32x128px
    static const char epd_bitmap_layer_adjust [] PROGMEM = {
        0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfc, 0x02, 0x02, 0x02, 0x02, 0x02, 0x82, 
        0xc2, 0x62, 0x62, 0x62, 0x62, 0x62, 0xe2, 0xc2, 0x02, 0x02, 0x02, 0x02, 0xfe, 0xfc, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 
        0x18, 0x18, 0x08, 0x08, 0x08, 0x18, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x07, 0x0e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf8, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x3f, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xc0, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0xff, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
        0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
        0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xfe, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x80, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 0x86, 0x8f, 
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xf1, 0xe1, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 
        0x03, 0x03, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
        0x60, 0x60, 0x63, 0x63, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // 'layer_extra', 32x128px
    static const char epd_bitmap_layer_extra [] PROGMEM = {
        0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfc, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xfe, 0xfc, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 
        0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x07, 0x0e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
        0x3b, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x30, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf8, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0xff, 0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 
        0xc0, 0x80, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x3f, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0xff, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 
        0x30, 0x19, 0x0f, 0x0f, 0x1f, 0x31, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xc0, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0xff, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
        0x08, 0x18, 0x18, 0x38, 0x78, 0xf8, 0xcf, 0x87, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf0, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0xff, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 
        0x63, 0x61, 0x21, 0x21, 0x21, 0x61, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x7f, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // 'layer_lower', 32x128px
    static const char epd_bitmap_layer_lower [] PROGMEM = {
        0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfc, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xfe, 0xfc, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 
        0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
        0x3f, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf8, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0xff, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x3f, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x39, 
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x39, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xc0, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0xff, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 
        0x38, 0x1e, 0x07, 0x07, 0x1c, 0x38, 0xf0, 0xff, 0x0f, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xfe, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xed, 
        0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf0, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
        0x11, 0x31, 0x31, 0x71, 0xf1, 0xf1, 0x9f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x7f, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // 'layer_qwerty', 32x128px
    static const char epd_bitmap_layer_qwerty [] PROGMEM = {
        0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfc, 0x02, 0x02, 0x02, 0x02, 0x82, 0xc2, 
        0x62, 0x62, 0x62, 0x62, 0x62, 0x62, 0xc2, 0x82, 0x02, 0x02, 0x02, 0x02, 0xfe, 0xfc, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x79, 
        0x60, 0x60, 0x60, 0x60, 0xe0, 0xe0, 0xb9, 0xbf, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x07, 0x0e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xff, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0xe0, 
        0x70, 0x3c, 0x0e, 0x0e, 0x38, 0x70, 0xe0, 0xfe, 0x1f, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xc0, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xdb, 
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x81, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 
        0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
        0x11, 0x31, 0x31, 0x71, 0xf1, 0xf1, 0x9f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xfe, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 
        0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x81, 0x81, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
        0x01, 0x01, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf0, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0xff, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
        0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x7f, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 
        0x30, 0x30, 0xf0, 0xf0, 0x30, 0x30, 0x1f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
        0x60, 0x60, 0x63, 0x63, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // 'layer_raise', 32x128px
    static const char epd_bitmap_layer_raise [] PROGMEM = {
        0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfc, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xfe, 0xfc, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x07, 0x0e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 
        0x04, 0x0c, 0x0c, 0x1c, 0x3c, 0x7c, 0x67, 0x43, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf8, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
        0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x3f, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0xff, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 
        0x31, 0x30, 0x10, 0x10, 0x10, 0x30, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x80, 0x80, 0x81, 0x81, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xfe, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x86, 0x8f, 
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xf1, 0xe1, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0xf0, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xb7, 
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x02, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x7f, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    
    // set oled layer image
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        oled_write_raw(epd_bitmap_layer_qwerty, sizeof(epd_bitmap_layer_qwerty));
        break;
        case _LOWER:
        oled_write_raw(epd_bitmap_layer_lower, sizeof(epd_bitmap_layer_lower));
        break;
        case _RAISE:
        oled_write_raw(epd_bitmap_layer_raise, sizeof(epd_bitmap_layer_raise));
        break;
        case _ADJUST:
        oled_write_raw(epd_bitmap_layer_adjust, sizeof(epd_bitmap_layer_adjust));
        break;
        case _EXTRA :
        oled_write_raw(epd_bitmap_layer_extra, sizeof(epd_bitmap_layer_extra));
        break;
    }
}

// render active mod locks
void oled_render_keymods(void) {
    led_t led_state = host_keyboard_led_state();
    if(led_state.num_lock){
        oled_write_P(PSTR("NumLk"), false);
    } else {
        oled_render_space();
    }
    if(led_state.caps_lock){
        oled_write_P(PSTR("CapLk"), false);
    } else {
        oled_render_space();
    }
    if(led_state.scroll_lock){
        oled_write_P(PSTR("ScrLk"), false);
    } else {
        oled_render_space();
    }
}

// Render Crkbd logo
static void oled_render_crkbd_logo(void) {
    static const char PROGMEM font_logo[16] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(font_logo, false);
};

// Render QMK logo
static void oled_render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[16] = {0x8F, 0x90, 0x91, 0x92, 0x93, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0};
    oled_write_P(qmk_logo, false);
}

// Render BM0 logo
static void oled_render_bmo_logo(void) {
    static const char PROGMEM bmo_logo[11] = {0x94, 0x95, 0x96, 0x97, 0x98, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0};
    oled_write_P(bmo_logo, false);
}

// Animation parameters
#define FRAME_DURATION 6000 // How long each frame lasts in milliseconds
uint32_t timer = 0;
uint8_t current_frame = 0;
// Render animation
static void oled_render_bmo_animation(void) {
    // BMO Still
    static const char epd_bitmap_bmo_still [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x40, 0x40, 0x40, 
        0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x77, 0x5d, 0x77, 0xff, 0x01, 0xfe, 0x03, 0xfd, 0xfd, 0xfd, 
        0xcd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xcd, 0xfd, 0xfd, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x3a, 0x29, 0x12, 0xff, 0x00, 0xff, 0xf8, 0xd7, 0xd7, 0x57, 
        0xd7, 0xd7, 0xd7, 0xf6, 0xf6, 0xf6, 0x77, 0xf7, 0xd7, 0xf7, 0xf8, 0xff, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0xf8, 0x04, 0x02, 0x02, 0x0d, 0x0d, 0x1d, 0x1c, 0x3f, 0x20, 0x1f, 0x3f, 0x37, 0xb6, 0x3c, 
        0x36, 0x37, 0x3f, 0x3f, 0x3f, 0x3e, 0xb2, 0x32, 0x3f, 0x3d, 0x3f, 0x1f, 0x00, 0x02, 0x7c, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // BMO Sleeping
    static const char epd_bitmap_bmo_sleep [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x62, 0x72, 0x5a, 0x4e, 0x46, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x60, 0xa0, 0xa0, 0xa0, 0xa0, 
        0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa4, 0xa6, 0xa5, 0xa4, 0xa0, 0xa0, 0x40, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x3b, 0xae, 0x3b, 0xff, 0x00, 0xff, 0x01, 0xfe, 0xfe, 0xee, 
        0xde, 0xee, 0xfe, 0x7e, 0x7e, 0xfe, 0xee, 0xde, 0xee, 0xfe, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0x9d, 0x94, 0x09, 0xff, 0x00, 0xff, 0xfc, 0xeb, 0x6b, 0x2b, 
        0x6b, 0xeb, 0xeb, 0xfb, 0xfb, 0x7b, 0x3b, 0x7b, 0xeb, 0xfb, 0xfc, 0xff, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x3c, 0x02, 0x01, 0x01, 0x06, 0x06, 0x0e, 0x0e, 0x1f, 0x10, 0x0f, 0x1f, 0x1b, 0x4b, 0x4e, 
        0x5b, 0x1b, 0x1f, 0x1f, 0x1f, 0x1f, 0x49, 0x49, 0x5f, 0x1e, 0x1f, 0x0f, 0x00, 0x01, 0x1e, 0x00
    };
    // BMO Dancing Frame 1
    static const char epd_bitmap_bmo_dance1 [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x40, 0x40, 0x40, 
        0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x77, 0x5d, 0x77, 0xff, 0x01, 0xfe, 0x03, 0xfd, 0xfd, 0xfd, 
        0xcd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xcd, 0xfd, 0xfd, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x3a, 0x29, 0x12, 0xff, 0x00, 0xff, 0xf8, 0xd7, 0xd7, 0x57, 
        0xd7, 0xd7, 0xd7, 0xf6, 0xf6, 0xf6, 0x77, 0xf7, 0xd7, 0xf7, 0xf8, 0xff, 0x00, 0x00, 0xf8, 0x00, 
        0x00, 0xf8, 0x04, 0x02, 0x02, 0x0d, 0x0d, 0x1d, 0x1c, 0x3f, 0x20, 0x1f, 0x3f, 0x37, 0xb6, 0x3c, 
        0x36, 0x37, 0x3f, 0x3f, 0x3f, 0x3e, 0xb2, 0x32, 0x3f, 0x3d, 0x3f, 0x1f, 0x00, 0x01, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // BMO Dancing Frame 2
    static const char epd_bitmap_bmo_dance2 [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xb8, 0xf8, 0xf8, 0x38, 0xd8, 0x68, 0xa8, 0xa8, 0xa8, 
        0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0x68, 0xd0, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x4e, 0x2b, 0x4e, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xfd, 
        0xfb, 0xfd, 0xef, 0xdf, 0xdf, 0xef, 0xfd, 0xfb, 0xfd, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x80, 0x40, 0x40, 0xaf, 0xa7, 0xa5, 0x82, 0xff, 0x00, 0xff, 0xff, 0xfa, 0xda, 0x8a, 
        0xda, 0xfa, 0xfa, 0xfe, 0xfe, 0xde, 0x4e, 0x5e, 0xfa, 0xbe, 0xff, 0xff, 0x00, 0x20, 0x1f, 0x00, 
        0x00, 0x1f, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x07, 0x04, 0x03, 0x07, 0x06, 0xf6, 0x07, 
        0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x16, 0x26, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // BMO Dancing Frame 3
    static const char epd_bitmap_bmo_dance3 [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x40, 0x40, 0x40, 
        0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x77, 0x5d, 0x77, 0xff, 0x01, 0xfe, 0x03, 0xfd, 0xfd, 0xed, 
        0xcd, 0xed, 0x7d, 0xfd, 0xfd, 0xfd, 0xed, 0xcd, 0xed, 0xfd, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x3a, 0x29, 0x12, 0xff, 0x00, 0xff, 0xf8, 0xd7, 0xd7, 0x57, 
        0xd7, 0xd7, 0xd7, 0xf6, 0xf6, 0xf6, 0x77, 0xf7, 0xd7, 0xf7, 0xf8, 0xff, 0x00, 0x00, 0xf8, 0x00, 
        0x00, 0xf8, 0x04, 0x02, 0x02, 0x0d, 0x0d, 0x1d, 0x1c, 0x3f, 0x20, 0x1f, 0x3f, 0x37, 0xb6, 0x3c, 
        0x36, 0x37, 0x3f, 0x3f, 0x3f, 0x3e, 0xb2, 0x32, 0x3f, 0x3d, 0x3f, 0x1f, 0x00, 0x01, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // BMO Dancing Frame 4
    static const char epd_bitmap_bmo_dance4 [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x40, 0x40, 0x40, 
        0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x77, 0x5d, 0x77, 0xff, 0x01, 0xfe, 0x03, 0xfd, 0xfd, 0xfd, 
        0xcd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xcd, 0xfd, 0xfd, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x3e, 0x40, 0x80, 0x80, 0x7f, 0x3a, 0x29, 0x12, 0xff, 0x00, 0xff, 0xf8, 0xd7, 0xd7, 0x57, 
        0xd7, 0xd7, 0xd7, 0xf6, 0xf6, 0xf6, 0x77, 0xf7, 0xd7, 0xf7, 0xf8, 0xff, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x0d, 0x1d, 0x1c, 0x3f, 0x20, 0x1f, 0x3f, 0x37, 0xb6, 0x3c, 
        0x36, 0x37, 0x3f, 0x3f, 0x3f, 0x3e, 0xb2, 0x32, 0x3f, 0x3d, 0x3f, 0x1f, 0x00, 0x01, 0x3e, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // BMO Dancing Frame 5
    static const char epd_bitmap_bmo_dance5 [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xb8, 0xf8, 0xf8, 0x38, 0xd8, 0x68, 0xa8, 0xa8, 0xa8, 
        0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0x68, 0xd0, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0xc0, 0x00, 0x00, 0x00, 0xff, 0x4e, 0x2b, 0x4e, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xfd, 
        0xfb, 0xfd, 0xef, 0xdf, 0xdf, 0xef, 0xfd, 0xfb, 0xfd, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x07, 0x08, 0x10, 0x10, 0xaf, 0xa7, 0xa5, 0x82, 0xff, 0x00, 0xff, 0xff, 0xfa, 0xda, 0x8a, 
        0xda, 0xfa, 0xfa, 0xfe, 0xfe, 0xde, 0x4e, 0x5e, 0xfa, 0xbe, 0xff, 0xff, 0x00, 0x20, 0xc0, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x07, 0x04, 0x03, 0x07, 0x06, 0x16, 0x27, 
        0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0xf6, 0x06, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x07, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // BMO Dancing Frame 6
    static const char epd_bitmap_bmo_dance6 [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x40, 0x40, 0x40, 
        0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x77, 0x5d, 0x77, 0xff, 0x01, 0xfe, 0x03, 0xfd, 0xfd, 0xed, 
        0xcd, 0xed, 0x7d, 0xfd, 0xfd, 0xfd, 0xed, 0xcd, 0xed, 0xfd, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x3e, 0x40, 0x80, 0x80, 0x7f, 0x3a, 0x29, 0x12, 0xff, 0x00, 0xff, 0xf8, 0xd7, 0xd7, 0x57, 
        0xd7, 0xd7, 0xd7, 0xf6, 0xf6, 0xf6, 0x77, 0xf7, 0xd7, 0xf7, 0xf8, 0xff, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x0d, 0x1d, 0x1c, 0x3f, 0x20, 0x1f, 0x3f, 0x37, 0xb6, 0x3c, 
        0x36, 0x37, 0x3f, 0x3f, 0x3f, 0x3e, 0xb2, 0x32, 0x3f, 0x3d, 0x3f, 0x1f, 0x00, 0x01, 0x3e, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // BMO dancing Animation frames array
    const char* bmo_dance_frames[] = {
        epd_bitmap_bmo_dance1,
        epd_bitmap_bmo_dance2,
        epd_bitmap_bmo_dance3,
        epd_bitmap_bmo_dance4,
        epd_bitmap_bmo_dance5,
        epd_bitmap_bmo_dance6
    };  
    // BMO dance animation frame sizes array
    uint16_t bmo_dance_frame_sizes[6] = {
        sizeof(epd_bitmap_bmo_dance1),
        sizeof(epd_bitmap_bmo_dance2),
        sizeof(epd_bitmap_bmo_dance3),
        sizeof(epd_bitmap_bmo_dance4),
        sizeof(epd_bitmap_bmo_dance5),
        sizeof(epd_bitmap_bmo_dance6)
    };

    // sleep animation if less than 10 WPM
    if (get_current_wpm() < 10){
        oled_write_raw_P(epd_bitmap_bmo_sleep, sizeof(epd_bitmap_bmo_sleep));
        }
    // still animation if less than 20 WPM
    else if (get_current_wpm() < 20){
        oled_write_raw_P(epd_bitmap_bmo_still, sizeof(epd_bitmap_bmo_still));
    }
    // Dance animation if less than 10 WPM
    else{
        if (timer_elapsed(timer) > (FRAME_DURATION / get_current_wpm())){
            // Set timer to updated time
            timer = timer_read();
            // Increment frame
            current_frame = (current_frame + 1) % (sizeof(bmo_dance_frames) / sizeof(bmo_dance_frames[0]));
            // Draw frame to OLED
            oled_write_raw_P(bmo_dance_frames[current_frame], bmo_dance_frame_sizes[current_frame]);
        }
    }
}

// Render WMP String
char wpm_str[12];
void oled_render_wpm(void) {
    sprintf(wpm_str, " %03d ", get_current_wpm());
    oled_write_P(wpm_str, false);
}

// Render Master OLED
void render_master_oled(void) {
    void oled_clear(void);
    oled_render_layer_state();
    oled_set_cursor(0, 13);
    oled_render_keymods();   
}

// Render Peripheral OLED
void render_peripheral_oled(void) { 
    oled_render_crkbd_logo();
    oled_render_qmk_logo();
    oled_write_P("crkbd", false);
    oled_render_space();
    oled_render_bmo_animation();
    oled_set_cursor(0, 13);
    oled_render_bmo_logo();
    oled_render_wpm();
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_master_oled();
    }       
    else {
        render_peripheral_oled();
    }
    return false;
}
#endif // OLED_ENABLE
