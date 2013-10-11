//
// Module			: mapreader.h
// Author			: bss
// Project			: TenDrops
// State			:
// Creation Date	: 2013-10-11
// Last Modification: 2013-10-11
// Description		: Read map from file.
//

#ifndef MAPREADER_H
#define MAPREADER_H

class MapReader
{
public:
    MapReader() = delete;

    static bool readMap(const char* filename, int* buffer);
    static void saveMap(const char* filename, int* buffer);
};

#endif // MAPREADER_H
