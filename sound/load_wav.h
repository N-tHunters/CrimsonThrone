#ifndef LOADWAV_H
#define LOADWAV_H

#include <AL/al.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>

bool is_big_endian();
std::int32_t convert_to_int(char* buffer, std::size_t len);
bool load_wav_file_header(std::ifstream& file,
                          std::uint8_t& channels,
                          std::int32_t& sampleRate,
                          std::uint8_t& bitsPerSample,
                          ALsizei& size);

char* load_wav(const std::string& filename,
               std::uint8_t& channels,
               std::int32_t& sampleRate,
               std::uint8_t& bitsPerSample,
               ALsizei& size);

bool load_wav_into_buffer(std::string& filename,
			  ALuint buffer);
#endif
