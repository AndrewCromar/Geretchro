import board
import busio
import displayio
from fourwire import FourWire
from adafruit_st7789 import ST7789

class GraphicsSystem:
    def __init__(self):
        displayio.release_displays()
        spi = busio.SPI(clock=board.GP18, MOSI=board.GP19)
        display_bus = FourWire(spi, command=board.GP20, chip_select=board.GP17, reset=board.GP21)
        
        self.dimensions = (320, 240)
        self.rotation = 90
        self.display = ST7789(display_bus, width=self.dimensions[0], height=self.dimensions[1], rotation=self.rotation)

    def testdraw(self):
        bitmap = displayio.Bitmap(self.dimensions[0], self.dimensions[1], 1)
        palette = displayio.Palette(1)
        palette[0] = 0x1cfc0c 
        
        tile_grid = displayio.TileGrid(bitmap, pixel_shader=palette)
        group = displayio.Group()
        group.append(tile_grid)

        # Use self.display to access it
        self.display.root_group = group