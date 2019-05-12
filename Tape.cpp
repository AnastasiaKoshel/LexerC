#include "Tape.h"

Tape::Tape(char * filename)
{
    std::ifstream file(filename, std::ifstream::in);
	if (file)
	{
        while (!file.eof())
		{
            char tmp;
            file.get(tmp);
            data.push_back(tmp);
		}

        data.pop_back();

		file.close();
	}
}
