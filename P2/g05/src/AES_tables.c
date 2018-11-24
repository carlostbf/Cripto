/***************************************************************************
AES_tables.c

Autores: Carlos Li Hu y David López Ramos
2018 EPS-UAM
 ***************************************************************************/

#include "../includes/AES_tables.h"

static const char DIRECT_SBOX[ROWS_PER_SBOX][COLUMNS_PER_SBOX][HEX_STRING_SIZE] = {
    { "63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"},
    { "ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"},
    { "b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"},
    { "04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"},
    { "09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"},
    { "53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"},
    { "d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"},
    { "51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"},
    { "cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"},
    { "60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"},
    { "e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"},
    { "e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"},
    { "ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"},
    { "70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"},
    { "e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"},
    { "8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"}
};

static const char INVERSE_SBOX[ROWS_PER_SBOX][COLUMNS_PER_SBOX][HEX_STRING_SIZE] = {
    { "52", "09", "6a", "d5", "30", "36", "a5", "38", "bf", "40", "a3", "9e", "81", "f3", "d7", "fb"},
    { "7c", "e3", "39", "82", "9b", "2f", "ff", "87", "34", "8e", "43", "44", "c4", "de", "e9", "cb"},
    { "54", "7b", "94", "32", "a6", "c2", "23", "3d", "ee", "4c", "95", "0b", "42", "fa", "c3", "4e"},
    { "08", "2e", "a1", "66", "28", "d9", "24", "b2", "76", "5b", "a2", "49", "6d", "8b", "d1", "25"},
    { "72", "f8", "f6", "64", "86", "68", "98", "16", "d4", "a4", "5c", "cc", "5d", "65", "b6", "92"},
    { "6c", "70", "48", "50", "fd", "ed", "b9", "da", "5e", "15", "46", "57", "a7", "8d", "9d", "84"},
    { "90", "d8", "ab", "00", "8c", "bc", "d3", "0a", "f7", "e4", "58", "05", "b8", "b3", "45", "06"},
    { "d0", "2c", "1e", "8f", "ca", "3f", "0f", "02", "c1", "af", "bd", "03", "01", "13", "8a", "6b"},
    { "3a", "91", "11", "41", "4f", "67", "dc", "ea", "97", "f2", "cf", "ce", "f0", "b4", "e6", "73"},
    { "96", "ac", "74", "22", "e7", "ad", "35", "85", "e2", "f9", "37", "e8", "1c", "75", "df", "6e"},
    { "47", "f1", "1a", "71", "1d", "29", "c5", "89", "6f", "b7", "62", "0e", "aa", "18", "be", "1b"},
    { "fc", "56", "3e", "4b", "c6", "d2", "79", "20", "9a", "db", "c0", "fe", "78", "cd", "5a", "f4"},
    { "1f", "dd", "a8", "33", "88", "07", "c7", "31", "b1", "12", "10", "59", "27", "80", "ec", "5f"},
    { "60", "51", "7f", "a9", "19", "b5", "4a", "0d", "2d", "e5", "7a", "9f", "93", "c9", "9c", "ef"},
    { "a0", "e0", "3b", "4d", "ae", "2a", "f5", "b0", "c8", "eb", "bb", "3c", "83", "53", "99", "61"},
    { "17", "2b", "04", "7e", "ba", "77", "d6", "26", "e1", "69", "14", "63", "55", "21", "0c", "7d"}
};

/*
static const char MIX_COLUMN_MATRIX[BYTES_PER_WORD][BYTES_PER_WORD][HEX_STRING_SIZE] = {
    { "02", "03", "01", "01"},
    { "01", "02", "03", "01"},
    { "01", "01", "02", "03"},
    { "03", "01", "01", "02"}
};

static const char INV_MIX_COLUMN_MATRIX[BYTES_PER_WORD][BYTES_PER_WORD][HEX_STRING_SIZE] = {
    { "0E", "0B", "0D", "09"},
    { "09", "0E", "0B", "0D"},
    { "0D", "09", "0E", "0B"},
    { "0B", "0D", "09", "0E"}
};
 */
uint64_t SB_AES_return(uint64_t B) {

    uint64_t SB = 0, aux2 = 0;
    uint8_t aux = 0, b[16] = {0}, sb[16] = {0};
    int i = 0;
    unsigned short fila = 0, columna = 0;
    char hex[2];

    for (i = 0; i < 8; i++) {
        aux = 0;
        b[i] = B >> 8 * (8 - (i + 1));
        /*printf("b%d 0x%"PRIx8"\n", i+1, b[i]);*/
        /*De cada Bi sacamos la fila y la columna con los correspondientes bits*/
        /*sacar fila*/
        aux = (b[i] >> 4) & 0x0F;
        /*printf("auxf%i 0x%"PRIx8"\n", i+1, aux);*/
        fila = (unsigned short) aux;
        /*printf("fila%i %d\n", i+1, fila);*/
        /*sacar columna*/
        aux = b[i] & 0x0F;
        /*printf("auxc%i 0x%"PRIx8"\n", i+1, aux);*/
        columna = (unsigned short) aux;
        /*printf("columna%i %d\n", i+1, columna);*/

        /*consultamos la tabla SBoxes*/
        /*hay que pasar los dos char leidos en las posiciones 0 y 1 a hexadecimal*/
        /*Ejemplo: "E8" sb[0] = "E", sb[1] = "8" */
        hex[0] = DIRECT_SBOX[fila][columna][0];
        hex[1] = DIRECT_SBOX[fila][columna][1];

        int num = (int) strtol(hex, NULL, 16);
        sb[i] = (uint8_t) num;
        /*printf("sb%d 0x%"PRIx8"\n", i+1, sb[i]);*/
    }

    /*juntamos los sbi para formar SB de 64 bits*/
    for (i = 0; i < 8; i++) {
        aux2 = (uint64_t) sb[i];
        SB = SB | (aux2 << (8 * (7 - i)));
    }

    return SB;

}