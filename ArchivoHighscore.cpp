#include "ArchivoHighscore.h"

ArchivoHighscore::ArchivoHighscore(const char *nombre){
        strcpy(this->nombre, nombre);
}
Highscore ArchivoHighscore::leerRegistro(int pos){
    Highscore reg;
    FILE *pHighscore;
    pHighscore=fopen(nombre, "rb");
    if(pHighscore==NULL) return reg;
    fseek(pHighscore, sizeof reg*pos,0);
    fread(&reg, sizeof reg,1, pHighscore);
    fclose(pHighscore);
    return reg;
}
int ArchivoHighscore::contarRegistros(){
    FILE *pHighscore;
    pHighscore=fopen(nombre, "rb");
    if(pHighscore==NULL) return -1;
    fseek(pHighscore, 0,2);
    int tam=ftell(pHighscore);
    fclose(pHighscore);
    return tam/sizeof(Highscore);
}
bool ArchivoHighscore::grabarRegistro(Highscore reg){
    FILE *pHighscore;
    pHighscore=fopen(nombre, "ab");
    if(pHighscore==NULL) return false;
    fwrite(&reg, sizeof reg, 1, pHighscore);
    fclose(pHighscore);
    return true;
}

void ArchivoHighscore::vaciarArchivo(){
    FILE *pHighscore;
    pHighscore=fopen(nombre, "wb");
    fclose(pHighscore);
}

ArchivoHighscore::~ArchivoHighscore(){
}
