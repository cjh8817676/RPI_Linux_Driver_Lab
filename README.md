# RPI_Linux_Driver_Lab

## [gpio_driver](./gpio_driver/)
使用Linux驅動操控GPIO，目的用於拉高與拉低電壓。
裡面做的事情是在樹莓派安裝可以開發Linux Kernel驅動的環境
並開發一個簡單的控制GPIO電壓輸出，以控制led的亮滅。沒經驗的可以先按照這個做。

## [Lab_1 1_chrdevbase](./1_chrdevbase/)
本章我們從 Linux驅動開發中最基礎的字符設備(1_chrdevbase)驅動開始，重點學習 Linux下字符設備驅動 動開發框架。本章會以一個虛擬的設備為例，

    1. 講解如何進行字符設備驅動開發，
    2. 以及如何編寫測試APP來測試驅動工作是否正常，
    
為以後的學習打下堅實的基礎。
