#include "SK68.h"

//for 48MHz
static void Delay100ns(uint16_t delay)
{
	while (delay--)
	{
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}

static void SK68_0code(GPIO_TypeDef *GPIOX, uint16_t GPIO_Pin)
{
	GPIOX->BSRR = GPIO_Pin;
	Delay100ns(1);
	GPIOX->BRR = GPIO_Pin;
	Delay100ns(4);
}

static void SK68_1code(GPIO_TypeDef *GPIOX, uint16_t GPIO_Pin)
{
	GPIOX->BSRR = GPIO_Pin;
	Delay100ns(4);
	GPIOX->BRR = GPIO_Pin;
	Delay100ns(1);
}

static void SK68_reset(GPIO_TypeDef *GPIOX, uint16_t GPIO_Pin)
{
	GPIOX->BRR = GPIO_Pin;
	Delay100ns(100);
}

static void SK68_convert_from_32b(GPIO_TypeDef *GPIOX, uint16_t GPIO_Pin,
		uint32_t *color)
{
	for (uint8_t i = 0; i < 24; i++)
	{
		(((*color << i) & 0x800000) == 0) ?
				SK68_0code(GPIOX, GPIO_Pin) : SK68_1code(GPIOX, GPIO_Pin);
	}
}

void SK68_set_color_multiLED(GPIO_TypeDef *GPIOX, uint16_t GPIO_Pin,
		uint32_t *color, uint8_t NumberOfLED)
{
	__set_PRIMASK(1); // disable global interrupt
	for (uint8_t i = 0; i < NumberOfLED; i++)
	{
		SK68_convert_from_32b(GPIOX, GPIO_Pin, color);
	}
	SK68_reset(LED_LOGO_GPIO_Port, LED_LOGO_Pin);
	__set_PRIMASK(0); // enable global interrupt
}

//RGB
void SK68_set_color(uint8_t LED_name, uint32_t *color)
{

	switch (LED_name)
	{
	case LED_LOGO:
		SK68_set_color_multiLED(LED_LOGO_GPIO_Port, LED_LOGO_Pin, color, 5);
		break;
	case LED_TOPLINE:
		SK68_set_color_multiLED(LED_TOPLINE_GPIO_Port, LED_TOPLINE_Pin, color, 2);
		break;
	case LED_SONIC:
		SK68_set_color_multiLED(LED_SONIC_GPIO_Port, LED_SONIC_Pin, color, 2);
		break;
	case LED_WARN:
		SK68_set_color_multiLED(LED_WARN_GPIO_Port, LED_WARN_Pin, color, 2);
		break;
	case LED_NET:
		SK68_set_color_multiLED(LED_NET_GPIO_Port, LED_NET_Pin, color, 2);
		break;
	case LED_SD:
		SK68_set_color_multiLED(LED_SD_GPIO_Port, LED_SD_Pin, color, 2);
		break;
	case LED_USB:
		SK68_set_color_multiLED(LED_USB_GPIO_Port, LED_USB_Pin, color, 2);
		break;
	case LED_INT:
		SK68_set_color_multiLED(LED_INT_GPIO_Port, LED_INT_Pin, color, 2);
		break;
	case LED_RING:
		SK68_set_color_multiLED(LED_RING_GPIO_Port, LED_RING_Pin, color, 2);
		break;
	case LED_LOG:
		SK68_set_color_multiLED(LED_LOG_GPIO_Port, LED_LOG_Pin, color, 4);
		break;
	case LED_UPDATE:
		SK68_set_color_multiLED(LED_UPDATE_GPIO_Port, LED_UPDATE_Pin, color, 3);
		break;
	case LED_RESTORE:
		SK68_set_color_multiLED(LED_RESTORE_GPIO_Port, LED_RESTORE_Pin, color, 3);
		break;
	case LED_BACKUP:
		SK68_set_color_multiLED(LED_BACKUP_GPIO_Port, LED_BACKUP_Pin, color, 3);
		break;
	case LED_RESTART:
		SK68_set_color_multiLED(LED_RESTART_GPIO_Port, LED_RESTART_Pin, color, 3);
		break;
	case LED_SCAN:
		SK68_set_color_multiLED(LED_SCAN_GPIO_Port, LED_SCAN_Pin, color, 3);
		break;
	case LED_TEST:
		SK68_set_color_multiLED(LED_TEST_GPIO_Port, LED_TEST_Pin, color, 3);
		break;
	}

}
