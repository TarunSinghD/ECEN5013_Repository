#include <stdint.h>

typedef union
{
	struct
	{
		uint32_t adc14SC:1;		/* bits 0      */
		uint32_t adc14ENC:1;		/* bits 1      */
		uint32_t Reserved:2;		/* bits 2..3   */
		uint32_t adc14ON:1;		/* bits 4      */
		uint32_t Reserved1:2;		/* bits 5..6   */
		uint32_t adc14MSC:1;		/* bits 7      */
		uint32_t adc14SHT0x:4;		/* bits 8..11  */
		uint32_t adc14SHT1x:4;		/* bits 12..15 */
		uint32_t adc14BUSY:1;		/* bits 16     */
		uint32_t adc14CONSEQx:2;	/* bits 17..18 */
		uint32_t adc14SSELx:3;		/* bits 19..21 */
		uint32_t adc14DIVx:3;		/* bits 22..24 */
		uint32_t adc14ISSH:1;		/* bits 25     */
		uint32_t adc14SHP:1;		/* bits 26     */
		uint32_t adc14SHSx:3;		/* bits 27..29 */
		uint32_t adc14PDIV:2;		/* bits 30..31 */
	} b;

	uint32_t w;

} ADC14_TYPE;

/* ADC14 base address */
#define ADC14_BASE 		(0x3fff4000)

/* ADC14 base pointer */
#define ADC14_BASE_PTR		((ADC14_TYPE *) ADC14_BASE)

/* Access bit 0 */
#define ADC14SC			(((ADC14_BASE_PTR)->b).adc14SC)

/* Access bits 8 through 11 */
#define ADC14SHt0x		(((ADC14_BASE_PTR)->b).adc14SHT0x)
