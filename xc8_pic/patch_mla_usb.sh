#!/bin/bash -xue
cd include/mla_usb/src
echo "diff --git a/src/usb_device.c b/src/usb_device.c
index 5805ecb..9f35f7b 100644
--- a/src/usb_device.c
+++ b/src/usb_device.c
@@ -1918,6 +1918,7 @@ static void USBCtrlTrfRxService(void)
                 //message when building with the XC8 compiler
                 #pragma warning push
                 #pragma warning disable 1088
+               #pragma warning disable 759
                 outPipes[0].pFunc();    //Call the user's callback function
                 #pragma warning pop
             #else
@@ -2654,7 +2655,10 @@ static void USBCtrlTrfInHandler(void)
         {
             if(outPipes[0].pFunc != NULL)
             {
+               #pragma warning push
+               #pragma warning disable 759
                 outPipes[0].pFunc();
+               #pragma warning pop
             }
             outPipes[0].info.bits.busy = 0;
         }
" | patch "$@"

