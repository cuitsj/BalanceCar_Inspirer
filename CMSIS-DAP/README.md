# STM32F103C8T6_CMSIS-DAP_SWO
-----------------------------
compile succ under keil uVision V5.15 with CMSIS 5.4.0
-----------------------------
Based x893's code on: https://github.com/x893/CMSIS-DAP

My contribution is:

1. Upgrade CMSIS-DAP version to V2.00 .
2. Enable SWO_UART function(USART1), no SWO_STREAM/SWO_MANCHESTER mode.
3. CDC function improved(USART2).
4. Added a Soft-Reset function for Cortex-M.
5. Added BluePill board support, Remapped or unRemap (refer to Docs).
6. Added STLINK_V2A board support (refer to Docs).
7. Minor changes, e.g. LED handling, project files re-group......

Thanks.
