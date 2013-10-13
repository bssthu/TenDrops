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

    static bool readMap(const char* filename, char *buffer);
    static void saveMap(const char* filename, char* buffer);
};

#endif // MAPREADER_H
