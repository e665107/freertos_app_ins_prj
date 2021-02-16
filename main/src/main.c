/* header files */
#include "soc_init.h"
#include "bsp_init.h"
#include "app_init.h"
#include "system_run.h"


 int main(void)
{
    /* system_init----------------------------------------------------------*/
    soc_init();
    bsp_init();
    /* application_init----------------------------------------------------------*/
    app_init();
    /* Infinite loop */
    run_the_system();
}


/************************ (C) COPYRIGHT Peasant zhang *****END OF FILE****/

