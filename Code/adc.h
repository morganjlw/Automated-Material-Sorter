/* ADC Header File */

#ifndef ADC_H_ /* Include guard */

// Defines
#define ADC_H_

//------------------------------
// Material thresholds
#define	ALUMINUM_MAX_ADC 200
//Back Left conner station
//000, 000, 831, 
//Station #10: 49, 48, 45, 47, 42
// Station #11: 15, 152, 15, 15, 15, 112

#define	STEEL_MAX_ADC 700
//230, 236, 131, 261, 179, 220, 224,161 
//Station #10: 528, 628, 625, 537, 590
//Station #11: 527, 515, 504, 352, 527, 423, 572, 496

#define WHITE_MAX_ADC 930
// 760, 764, 764, 762, 750, 800 
// white tests 929, 988, 993, 991 992, 979, 942, 969, 931, 928
//Station #10: 884, 875, 888, 887, 885
// Station #11: 899, 935, 896, 896, 927, 880, 896

#define BLACK_MAX_ADC 1024
// 799, 790, 787, 792, 800, 
// black tests 961, 961, 960, 964, 963, 953, 950,
//Station #10: 946, 939, 951, 941, 945, 947
// Station #11: 967, 960, 952, 960, 975, 961
//------------------------------

//Prototypes
void adcInit(void);

// Define the global variable that can be used in every function
volatile unsigned int ADC_result;
volatile unsigned int ADC_result_flag;
volatile unsigned int ADC_count;
volatile int Object_result;

// Sorted Material global variables
volatile unsigned int BL_count;
volatile unsigned int WH_count;
volatile unsigned int ST_count;
volatile unsigned int AL_count;
 
#endif //ADC_H_