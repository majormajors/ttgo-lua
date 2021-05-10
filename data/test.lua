width = epd.width()
height = epd.height()

midpoint = {
    x = width / 2,
    y = height / 2
}

epd.power_on()
epd.clear()

epd.write_string("Hello from Lua", 100, 100)
epd.write_string(
        "Screen size " .. width .. "," .. height,
        300,
        300)

epd.draw_hline(0, height - 100, width, 16)
epd.draw_hline(0, 100, width, 16)
epd.draw_vline(width - 100, 0, height, 16)
epd.draw_vline(100, 0, height, 16)

r = math.min(width, height) / 2
epd.draw_circle(midpoint.x, midpoint.y, r, 16)

square_origin = {
    x = midpoint.x - r,
    y = midpoint.y - r
}
square_length = r * 2
epd.draw_rect(square_origin.x, square_origin.y, square_length, square_length, 16)

epd.render()
epd.power_off()