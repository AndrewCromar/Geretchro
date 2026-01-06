import graphics
import time

gui = graphics.GraphicsEngine()
pos_x = 0

while True:
    gui.clear()
    
    pos_x = (pos_x + 2) % 160
    
    gui.draw_square(pos_x, 30, 20, 0x1cfc0c)
    gui.draw_square(100, 10, 5, 0xFF0000)
    gui.draw_square(10, 80, 10, 0x0000FF)
    
    for i in range(30):
        gui.draw_pixel(i + 20, 110, 0xFFFFFF)
    
    gui.render()