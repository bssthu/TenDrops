//
// Module			: mapreader.cpp
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-11
// Last Modification: 2013-10-11
// Description		:
//

#include "mapreader.h"
#include <stdio.h>

bool MapReader::readMap(const char *filename, int* buffer)
{
    FILE* fp = nullptr;
    fopen_s(&fp, filename, "rt");
    if (nullptr == fp)
    {
        return false;
    }

    for (int i = 0; i < 36; i++)
    {
        if (fscanf(fp, "%d", &buffer[i]) != 1)
        {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);
    return true;
}

void MapReader::saveMap(const char *filename, int* buffer)
{
    FILE* fp = nullptr;
    fopen_s(&fp, filename, "wt");
    if (nullptr == fp)
    {
        return;
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            fprintf(fp, "%d ", buffer[i * 6 + j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return;
}
