#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* RIFF = "RIFF";

int main(int args,char* argv[]){
    if(args<2)
        return 0;
    for(int i=1;i<args;i++){
        char RIFFbuf[5]={0};
        char outFileName[32];
        int wavFileLen=0;
        int ExCount = 1;
        printf("Extracting %s\n",argv[i]);
        FILE *pfInput=NULL,*pfOutput=NULL;
        pfInput = fopen(argv[i],"rb+");
        if(!pfInput){
            printf("Opening file %s failed.\n",argv[i]);
            return 0;
        }
        while(!feof(pfInput)){
            while(fread(RIFFbuf,4,1,pfInput)==1){
                if(strcmp(RIFF,RIFFbuf)==0){
                    printf("Found .wav header\n");
                    fread(&wavFileLen,4,1,pfInput);
                    printf(".wav file size: %d\n",wavFileLen);
                    char* pMem=NULL;
                    pMem=malloc(wavFileLen);
                    if(!pMem){
                        printf("malloc failed.\n");
                        return 0;
                    }
                    fread(pMem,wavFileLen,1,pfInput);
                    sprintf(outFileName,"%d_%d.wav",i,ExCount++);
                    pfOutput=fopen(outFileName,"wb+");
                    if(!pfOutput){
                        printf("Creating file failed.\n");
                        return 0;
                    }
                    fwrite(RIFF,4,1,pfOutput);
                    fwrite(&wavFileLen,4,1,pfOutput);
                    fwrite(pMem,wavFileLen,1,pfOutput);
                    fclose(pfOutput);
                    free(pMem);
                    break;
                }
            }
        }
        if(ExCount==1){
            printf("No .wav header found.\n");
        }
        fclose(pfInput);
    }
    system("pause");
    return 1;
}