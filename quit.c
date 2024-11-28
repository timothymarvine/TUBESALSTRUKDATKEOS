void QUIT(){
    printf("Apakah kamu ingin menyimpan data sesi sekarang (Y/N)?\n"); STARTWORD();
    if (WordCompareString(currentword, "Y"))
    {
       return SAVE();
    }else
    {
        printf("kamu keluar dari PURRMART.\n");
        printf("Dadah ^_^/ \n");
    }
    
    
}