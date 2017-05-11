#!/bin/bash -xue
cat $0 | sed '1,/^#- PATCH -#$/d' | ( cd include/mla_usb/src; patch "$@"; )
exit

#- PATCH -#

diff --git a/src/usb_device.c b/src/usb_device.c
index 5805ecb..4e1c03f 100644
--- a/src/usb_device.c
+++ b/src/usb_device.c
@@ -1494,7 +1494,7 @@ void USBCtrlEPAllowDataStage(void)
     {
         //Prepare EP0 OUT to receive the first OUT data packet in the data stage sequence.
         pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
-        pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&CtrlTrfData);
+        pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(CtrlTrfData);
         pBDTEntryEP0OutNext->STAT.Val = _DAT1|(_DTSEN & _DTS_CHECKING_ENABLED);
         pBDTEntryEP0OutNext->STAT.Val |= _USIE;
     }
@@ -1511,7 +1511,7 @@ void USBCtrlEPAllowDataStage(void)
 
 	    //Cnt should have been initialized by responsible request owner (ex: by
 	    //using the USBEP0SendRAMPtr() or USBEP0SendROMPtr() API function).
-		pBDTEntryIn[0]->ADR = ConvertToPhysicalAddress(&CtrlTrfData);
+		pBDTEntryIn[0]->ADR = ConvertToPhysicalAddress(CtrlTrfData);
 		pBDTEntryIn[0]->STAT.Val = _DAT1|(_DTSEN & _DTS_CHECKING_ENABLED);
         pBDTEntryIn[0]->STAT.Val |= _USIE;
     }
@@ -1881,7 +1881,7 @@ static void USBCtrlTrfRxService(void)
     if(outPipes[0].wCount.Val > 0)
     {
         pBDTEntryEP0OutNext->CNT = USB_EP0_BUFF_SIZE;
-        pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(&CtrlTrfData);
+        pBDTEntryEP0OutNext->ADR = ConvertToPhysicalAddress(CtrlTrfData);
         if(pBDTEntryEP0OutCurrent->STAT.DTS == 0)
         {
             pBDTEntryEP0OutNext->STAT.Val = _DAT1|(_DTSEN & _DTS_CHECKING_ENABLED);
@@ -1918,6 +1918,7 @@ static void USBCtrlTrfRxService(void)
                 //message when building with the XC8 compiler
                 #pragma warning push
                 #pragma warning disable 1088
+               #pragma warning disable 759
                 outPipes[0].pFunc();    //Call the user's callback function
                 #pragma warning pop
             #else
@@ -1991,7 +1992,7 @@ static void USBStdSetCfgHandler(void)
 	}
 
     //clear the alternate interface settings
-    memset((void*)&USBAlternateInterface,0x00,USB_MAX_NUM_INT);
+    memset((void*)USBAlternateInterface,0x00,USB_MAX_NUM_INT);
 
     //Stop trying to reset ping pong buffer pointers
     USBPingPongBufferReset = 0;
@@ -2177,7 +2178,7 @@ static void USBStdGetStatusHandler(void)
 
     if(inPipes[0].info.bits.busy == 1)
     {
-        inPipes[0].pSrc.bRam = (uint8_t*)&CtrlTrfData;        // Set Source
+        inPipes[0].pSrc.bRam = (uint8_t*)CtrlTrfData;        // Set Source
         inPipes[0].info.bits.ctrl_trf_mem = USB_EP0_RAM;      // Set memory type
         inPipes[0].wCount.v[0] = 2;                           // Set data count
     }//end if(...)
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
diff --git a/src/usb_device_hid.c b/src/usb_device_hid.c
index 7574599..d067880 100644
--- a/src/usb_device_hid.c
+++ b/src/usb_device_hid.c
@@ -168,7 +168,7 @@ void USBCheckHIDRequest(void)
                 if(USBActiveConfiguration == 1)
                 {
                     USBEP0SendROMPtr(
-                        (const uint8_t*)&configDescriptor1 + 18,		//18 is a magic number.  It is the offset from start of the configuration descriptor to the start of the HID descriptor.
+                        (const uint8_t*)configDescriptor1 + 18,		//18 is a magic number.  It is the offset from start of the configuration descriptor to the start of the HID descriptor.
                         sizeof(USB_HID_DSC)+3,
                         USB_EP0_INCLUDE_ZERO);
                 }
