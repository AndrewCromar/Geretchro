import board
import busio
import displayio
from fourwire import FourWire
from adafruit_st7789 import ST7789

class GraphicsEngine:
    def __init__(self):
        displayio.release_displays()
        
        spi = busio.SPI(clock=board.GP18, MOSI=board.GP19)
        display_bus = FourWire(
            spi, 
            command=board.GP20, 
            chip_select=board.GP17, 
            reset=board.GP21,
            baudrate=62500000
        )

        self.width = int(320 / 4)
        self.height = int(240 / 4)
        
        self.display = ST7789(
            display_bus, 
            width=320, 
            height=240, 
            rotation=90, 
            auto_refresh=False
        )

        self.stage = displayio.Group(scale=2)
        self.display.root_group = self.stage

        self.max_sprites = 40 
        self.sprite_pool = []
        
        self.shared_bmp = displayio.Bitmap(1, 1, 1)
        
        for _ in range(self.max_sprites):
            pal = displayio.Palette(1)
            pal[0] = 0x000000
            
            tg = displayio.TileGrid(self.shared_bmp, pixel_shader=pal)
            
            container = displayio.Group()
            container.append(tg)
            container.x = -100 # Hide it
            
            self.stage.append(container)
            self.sprite_pool.append(container)
        
        self.pool_index = 0

    def clear(self):
        """Move used sprites off-screen"""
        for i in range(self.pool_index):
            self.sprite_pool[i].x = -100
        self.pool_index = 0

    def draw_square(self, x, y, size, color):
        """Uses group scaling to resize a 1x1 pixel into a square"""
        if self.pool_index < self.max_sprites:
            container = self.sprite_pool[self.pool_index]
            tg = container[0]
            
            container.x = int(x)
            container.y = int(y)
            container.scale = int(size)
            tg.pixel_shader[0] = color
            
            self.pool_index += 1

    def draw_pixel(self, x, y, color):
        self.draw_square(x, y, 1, color)

    def render(self):
        self.display.refresh()