epd.power_on();
epd.clear();

epd.write_string("Hello TTGO from Lua", 100, 100);
epd.write_string(
        "Screen size " .. epd.width() .. "," .. epd.height(),
        300,
        300);

epd.draw_hline(0, epd.height() - 100, epd.width(), 16);
epd.draw_vline(epd.width() - 100, 0, epd.height(), 16);

epd.render();
epd.power_off();