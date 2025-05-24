// Основные настройки дисплея
#define ST7789_DRIVER     // Используем драйвер ST7789
#define TFT_WIDTH  240    // Ширина экрана
#define TFT_HEIGHT 240    // Высота экрана

// Настройки SPI для Milk-V Duo
#define TFT_MOSI  10      // MOSI (SDA)
#define TFT_SCLK  9       // SCK (SCL)
#define TFT_CS    27       // Chip select (если используется)
#define TFT_DC    2      // Data/Command
#define TFT_RST   19       // Reset

// Настройки цветов
#define TFT_INVERSION_ON
// #define TFT_RGB_ORDER TFT_BGR  // Раскомментируйте если цвета неправильные

// Шрифты
#define LOAD_GLCD   // Стандартный шрифт
#define LOAD_FONT2  // Дополнительные шрифты
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8

// Частота SPI
//#define SPI_FREQUENCY  27000000  // 27 MHz
#define SPI_FREQUENCY 20000000 // 20MHz
//#define SPI_FREQUENCY  40000000  // 40 MHz
