#ifdef NAODLL_EXPORT
#define NAODLL_API __declspec(dllexport) 
#else
#define NAODLL_API __declspec(dllimport) 
#endif

#include <iostream>

extern "C" {
    NAODLL_API void NaoSit();
    NAODLL_API void NaoTalk(std::string phraseToSay);
	NAODLL_API void NaoWalk();
}